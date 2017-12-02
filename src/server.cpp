#include "server.hpp"
#include <iostream>
#include <exception>
#define SOCKET_INIT_FAILED "Socket initalization failed"
using namespace std;

#define QUEUE_SIZE 5
#define MAX_CLIENTS 100

Server::Server(const int& portNumber)
{
    this->portNumber = portNumber;

    try{
        initializeNewSocket();
    }
    catch(exception& e){
        cout<<e.what();
    }

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


void Server::runServer()
{

}

