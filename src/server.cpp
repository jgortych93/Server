#include "server.hpp"
#include "ActionArguments.h"
#include <iostream>
#include <exception>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include<QtCore/qdebug.h>

using namespace std;

#define SOCKET_INIT_FAILED "Socket initalization failed"
#define BIND_FAILED "Error on binding"
#define LISTEN_ERROR "Error on listen call"
#define ACCEPT_ERROR "Cannot accept connection"
#define BUFFER_SIZE 300
#define NAME_BUFFER_SIZE 3

uint Server::numberOfThreads = 0;


Server::Server(const int& portNumber)
{
    this->portNumber = portNumber;

    try{
        initializeNewSocket();
    }
    catch(exception& e){
        qDebug()<<e.what();
    }

    bzero(reinterpret_cast<char *> (&serverAddress), sizeof(serverAddress));
    fillServerAddressStruct();

}

void Server::initializeNewSocket()
{
    this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == 0)
    {
        throw runtime_error(SOCKET_INIT_FAILED);
    }
    int enable = 1;
    if (setsockopt(this->socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw runtime_error(strerror(errno));
}

void Server::fillServerAddressStruct()
{
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(static_cast<uint16_t>(this->portNumber));
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void Server::bindSocket()
{
    if (bind(socketDescriptor, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0)
    {
            throw runtime_error(strerror(errno));
    }
}

void Server::listenOnSocket()
{
    if (listen(socketDescriptor, QUEUE_SIZE) == -1)
        throw runtime_error(LISTEN_ERROR);

}


void Server::runServer()
{
    bindSocket();
    listenOnSocket();

    struct sockaddr_in tmpAddress;
    uint clientAddressLength = sizeof(tmpAddress);



    while(Server::numberOfThreads < QUEUE_SIZE)
    {
        qDebug()<<"listening";

        const int clientDescriptor = accept(socketDescriptor, reinterpret_cast<struct sockaddr*>(&tmpAddress), &clientAddressLength);

        if (clientDescriptor == 0)
        {
              qDebug()<<ACCEPT_ERROR<<endl;
              continue;
        }

        qDebug()<<"New connection"<<endl;

        ++Server::numberOfThreads;


        ClientObject newClientObject;
        newClientObject.setUserId(Server::numberOfThreads);
        newClientObject.setConnectionDesc(clientDescriptor);
        newClientObject.setClientAddress(tmpAddress);
        this->clients[numberOfThreads-1] = newClientObject;

        ActionArguments actionArguments(newClientObject, this);

        pthread_create(&clientThreads[Server::numberOfThreads], NULL, action, static_cast<void*>(&actionArguments));
    }

}

void* Server::action(void* args)
{
    ActionArguments arguments = *(static_cast<ActionArguments*>(args));

    char messageBuffer[BUFFER_SIZE];
    bzero(messageBuffer, BUFFER_SIZE+1);
    char nameBuffer[NAME_BUFFER_SIZE];
    bzero(nameBuffer, NAME_BUFFER_SIZE+1);

    ClientObject* clientObject = &arguments.client;
    const Server* serverInstance = arguments.server;

    // default name is thread number
    snprintf(nameBuffer, NAME_BUFFER_SIZE, "%d", Server::numberOfThreads);
    clientObject->setName(nameBuffer);

    const int clientDesc = clientObject->getConnectionDesc();

    try
    {
        clientObject->sendMessage("Welcome to the Server. Please type your message or configure your data by writing '~options'"
                                 "To quit send '~quit' message\n");
        qDebug()<<"Initial message send!\n"<<endl;
    }
    catch(exception& e){
        qDebug()<<e.what();
    }

    do{

        bzero(messageBuffer, BUFFER_SIZE);

        if (read(clientObject->getConnectionDesc(), messageBuffer, BUFFER_SIZE-1) == 0)
            throw runtime_error(strerror(errno));

        if (strncmp(messageBuffer, "~options", BUFFER_SIZE) != 0){
            char *clientId = new char[BUFFER_SIZE];
            bzero(clientId,BUFFER_SIZE);
            char* message = new char[BUFFER_SIZE];

            snprintf(message, BUFFER_SIZE, "%s: %s",clientObject->getName(), messageBuffer);
            qDebug()<<message;
            serverInstance->broadcastMessage(message, clientDesc);

            delete[] clientId;
            delete[] message;

        }
        else{
            serverInstance->handleOptionsInterface(clientObject);
            continue;
        }
    }while(strncmp(messageBuffer, "~quit", BUFFER_SIZE) != 0);

}

void Server::broadcastMessage(const char* message, const int& clientDescriptor) const
{
    for (uint i=0; i<Server::numberOfThreads; ++i){
        if (this->clients[i].getConnectionDesc() != clientDescriptor){
            this->clients[i].sendMessage(message);
        }
    }
}

void Server::handleOptionsInterface(ClientObject* client) const
{
    static const char* optionsMessage = "Options:\n\n\t1.Change the nickname.\n";
    client->sendMessage(optionsMessage);

    char* messageBuffer = new char[BUFFER_SIZE];
    bzero(messageBuffer, BUFFER_SIZE);

    if (read(client->getConnectionDesc(), messageBuffer, BUFFER_SIZE-1) == 0)
        throw runtime_error(strerror(errno));

    char* oldName;
    char* messageAboutChangingNick;

    switch(atoi(messageBuffer)){
    case 1:
        client->sendMessage("\tPlease type the new nickname and press enter.\n");
        oldName = client->getName();
        try {
        this->handleNickChanging(client);
        } catch (exception &e) {
            qDebug()<<e.what();
            client->sendMessage("Reading the name failed");
        }

        client->sendMessage("NAME CHANGED SUCCESSFULLY\n");

        messageAboutChangingNick = new char[BUFFER_SIZE];
        bzero(messageAboutChangingNick, BUFFER_SIZE);
        snprintf(messageAboutChangingNick, BUFFER_SIZE, "%s changed name to : %s",oldName, client->getName());
        this->broadcastMessage(messageAboutChangingNick, client->getConnectionDesc());
        delete[] messageAboutChangingNick;

        break;
    default:
        client->sendMessage("\tGiven option not found.\n");
        break;
    }

    delete[] messageBuffer;

}

void Server::handleNickChanging(ClientObject *client) const
{
    char* messageBuffer = new char[BUFFER_SIZE];
    bzero(messageBuffer, BUFFER_SIZE);

    if (read(client->getConnectionDesc(), messageBuffer, BUFFER_SIZE-1) == 0)
            throw exception();

    client->setName(messageBuffer);

    delete [] messageBuffer;

}

