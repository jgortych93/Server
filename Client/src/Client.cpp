#include "Client.hpp"
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <QtCore/qdebug.h>

#define SOCKET_INIT_FAILED "Socket initalization failed"
#define BIND_FAILED "Error on binding"
#define LISTEN_ERROR "Error on listen call"
#define ACCEPT_ERROR "Cannot accept connection"
#define SENDING_ERROR "Sending to client has failed"
#define CONNECTION_ERROR "Cannot connect to socket"
#define ADDRESS_ERROR "Wrong ip address"
#define CONNECT_ERROR "CONNECT ERROR"
#define BUFFER_SIZE 300

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
    if (serverFileDescriptor == 0)
    {
        throw runtime_error(SOCKET_INIT_FAILED);
    }
}

void Client::fillServerAddressStruct()
{
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(static_cast<uint16_t>(this->serverPort));
    this->resolveAddress();
}

void Client::resolveAddress()
{

    if (!inet_aton(this->ipAddress, (&this->serverAddress.sin_addr)))
        throw runtime_error(ADDRESS_ERROR);
}


void Client::connectToServer()
{
    if (connect(this->serverFileDescriptor, reinterpret_cast<struct sockaddr*>(&this->serverAddress), sizeof(serverAddress)) == -1)
        throw runtime_error(CONNECT_ERROR);

    this->communicateWithServer();
}

void Client::communicateWithServer()
{
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE+1);
    qDebug("Type message to send please: \n");

    pthread_create(new pthread_t(), NULL, handleTextEntering, static_cast<void*>(&this->serverFileDescriptor));

    while(1){
        readMessage(buffer);
    }

}

void Client::readMessage(char *buffer) const
{
    if (read(this->serverFileDescriptor, buffer, BUFFER_SIZE) == -1)
    {
        throw runtime_error(strerror(errno));
    }
    else
    {
        qDebug()<<buffer<<endl;
        bzero(buffer, BUFFER_SIZE+1);
    }
}

void* Client::handleTextEntering(void * serverDesc)
{
    while(1){

        QTextStream qtin(stdin);
        QString line = qtin.readLine();

        QByteArray ba = line.toLatin1();
        char *messageBuffer = ba.data();

        sendMessage(messageBuffer, *static_cast<int*>(serverDesc));

    }
}

void Client::sendMessage(const char *message, const int& serverDesc)
{
    const int sendingStatus =  static_cast<const int>(write(serverDesc, message, strlen(message)));

    if (sendingStatus < 0)
        throw runtime_error(SENDING_ERROR);

}
