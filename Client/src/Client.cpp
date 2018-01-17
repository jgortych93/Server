#include "Client.hpp"
#include <exception>

#define SOCKET_INIT_FAILED "Socket initalization failed"
#define BIND_FAILED "Error on binding"
#define LISTEN_ERROR "Error on listen call"
#define ACCEPT_ERROR "Cannot accept connection"
#define SENDING_ERROR "Sending to client has failed"
#define BUFFER_SIZE 300
#define QUEUE_SIZE 5

Client::Client(const int& port)
{
        this->port = port;

        initializeNewSocket();

        fillServerAddressStruct();

}

void Client::initializeNewSocket()
{
    this->fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor = 0)
    {
        throw runtime_error(SOCKET_INIT_FAILED);
    }
}

void Client::fillServerAddressStruct()
{
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(this->port);
    this->address.sin_addr.s_addr = INADDR_ANY;
}

void Client::bindSocket()
{
    if (bind(this->fileDescriptor, (struct sockaddr*)&(this->address), sizeof(address)) < 0)
    {
            throw runtime_error(BIND_FAILED);
    }
}

void Client::listenOnSocket()
{
    if (listen(this->fileDescriptor, QUEUE_SIZE) == -1)
        throw runtime_error(LISTEN_ERROR);
}

void Client::startClient()
{
    bindSocket();
    listenOnSocket();

    while(1)
    {
        cout<<"listening";

        const int serverDescriptor = accept(this->fileDescriptor, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (serverDescriptor == 0)
        {
              throw runtime_error(ACCEPT_ERROR);
        }

        cout<<"New connection"<<endl;
    }
}
