#include "ClientObject.hpp"
#include <unistd.h>
#include <string.h>
#include <stdexcept>
#include <QtCore/qdebug.h>

#define SENDING_ERROR "Sending to above user failed"

using namespace std;

void ClientObject::sendMessage(const char *message) const
{
    const int sendingStatus =  static_cast<const int>(write(this->connectionDesc, message, strlen(message)));

    if (sendingStatus < 0){
        qDebug()<<this->name;
        throw runtime_error(SENDING_ERROR);
    }
}
