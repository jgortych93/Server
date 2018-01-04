#include "server.hpp"
#include <iostream>
#include <exception>
#include <string.h>
#include <unistd.h>

using namespace std;

#define SOCKET_INIT_FAILED "Socket initalization failed"
#define BIND_FAILED "Error on binding"
#define LISTEN_ERROR "Error on listen call"
#define ACCEPT_ERROR "Cannot accept connection"
#define BUFFER_SIZE 300

Server::Server(const int& portNumber)
{
    this->portNumber = portNumber;

    try{
        initializeNewSocket();
    }
    catch(exception& e){
        cout<<e.what();
    }

    fillServerAddressStruct();

    bzero((char *) &serverAddress, sizeof(serverAddress));

}

void Server::initializeNewSocket()
{
    this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor = 0)
    {
        throw runtime_error(SOCKET_INIT_FAILED);
    }
}

void Server::fillServerAddressStruct()
{
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->portNumber);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void Server::bindSocket()
{
    if (bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
            throw runtime_error(BIND_FAILED);
    }
}

void Server::listenOnSocket()
{
    if (listen(socketDescriptor, QUEUE_SIZE) == -1)
        throw runtime_error(LISTEN_ERROR);
}

void Server::runServer()
{
    listenOnSocket();

    uint clientAddressLength = sizeof(clientAddress);

    numberOfThreads = 0;

    while(numberOfThreads < QUEUE_SIZE)
    {
        cout<<"listening";

        const int clientDescriptor = accept(socketDescriptor, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientDescriptor == 0)
        {
              throw runtime_error(ACCEPT_ERROR);
        }

        cout<<"New connection"<<endl;

        pthread_create(&clientThreads[numberOfThreads], NULL, action, (void*)(intptr_t)clientDescriptor);
        pthread_join(clientThreads[numberOfThreads], NULL);

        ++numberOfThreads;

    }

}

void* Server::action(void* clientDesc)
{
    char messageBuffer[BUFFER_SIZE];
    bzero(messageBuffer, BUFFER_SIZE+1);

    read(*(int *)clientDesc, messageBuffer, BUFFER_SIZE);

    ClientObject client;
    client.setUserId(numberOfThreads);




}

