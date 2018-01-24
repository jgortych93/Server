#include "Client.hpp"
#include <stdexcept>
#include <iostream>

#define SOCKET_INIT_FAILED "Socket initalization failed"
#define BIND_FAILED "Error on binding"
#define LISTEN_ERROR "Error on listen call"
#define ACCEPT_ERROR "Cannot accept connection"
#define SENDING_ERROR "Sending to client has failed"
#define CONNECTION_ERROR "Cannot connect to socket"
#define ADDRESS_ERROR "Wrong ip address"
#define CONNECT_ERROR "CONNECT ERROR"
#define BUFFER_SIZE 300
#define QUEUE_SIZE 5

using namespace std;

Client::Client(const char* ipAddress, const int& port)
{
        this->serverPort = port;
        this->ipAddress = ipAddress;

        initializeNewSocket();

        fillServerAddressStruct();

}

void Client::initializeNewSocket()
{
    this->serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFileDescriptor = 0)
    {
        throw runtime_error(SOCKET_INIT_FAILED);
    }
}

void Client::fillServerAddressStruct()
{
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->serverPort);
    this->resolveAddress();
}

void Client::resolveAddress()
{

    if (!inet_aton(this->ipAddress, (&this->serverAddress.sin_addr)))
        throw runtime_error(ADDRESS_ERROR);
}


void Client::connectToServer()
{
    if (connect(this->serverFileDescriptor, (struct sockaddr*)&(this->serverAddress), sizeof(serverAddress)) == -1)
        throw runtime_error(CONNECT_ERROR);

    this->communicateWithServer();
}

void Client::communicateWithServer()
{
    //readMessage();
}
