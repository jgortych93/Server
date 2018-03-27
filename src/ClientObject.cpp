#include "ClientObject.hpp"
#include <unistd.h>
#include <string.h>
#include <stdexcept>
#include <QtCore/qdebug.h>

#define SENDING_ERROR "Sending to above user failed"

using namespace std;

uint8_t ClientObject::getThreadNumber() const
{
    return threadNumber;
}

void ClientObject::setThreadNumber(const uint8_t &value)
{
    threadNumber = value;
}

void ClientObject::sendMessage(const char *message) const
{
    const int sendingStatus =  static_cast<const int>(write(this->connectionDesc, message, strlen(message)));

    if (sendingStatus < 0){
        qDebug()<<this->name;
        throw runtime_error(SENDING_ERROR);
    }
}

ClientObject::ClientObject(const int &descriptor, const sockaddr_in &address)
{
    this->name = new char[NAME_SIZE+1];

    this->connectionDesc = descriptor;
    this->clientAddress = address;
}
