#include "server.hpp"
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

        pthread_create(&clientThreads[Server::numberOfThreads], NULL, action, static_cast<void*>(&newClientObject));
        pthread_join(clientThreads[Server::numberOfThreads], NULL);
    }

}

void* Server::action(void* client)
{

    char messageBuffer[BUFFER_SIZE];
    bzero(messageBuffer, BUFFER_SIZE+1);
    char nameBuffer[NAME_BUFFER_SIZE];
    bzero(nameBuffer, NAME_BUFFER_SIZE+1);

    ClientObject clientObject = *static_cast<ClientObject *>(client);

    // default name is thread number
    snprintf(nameBuffer, NAME_BUFFER_SIZE, "%d", Server::numberOfThreads);
    clientObject.setName(nameBuffer);


    try
    {
        clientObject.sendMessage("Test message\n", clientObject.getSocketDescriptor());
        qDebug()<<"Initial message send!\n"<<endl;
    }
    catch(exception& e){
        qDebug()<<e.what();
    }

    read(clientObject.getSocketDescriptor(), messageBuffer, BUFFER_SIZE);

}

