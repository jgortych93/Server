#include "ClientObject.hpp"
#include <unistd.h>
#include <stdexcept>

#define SENDING_ERROR "Sending to client has failed"

using namespace std;

void ClientObject::sendMessage(const char *message) const
{
    const int sendingStatus =  write(this->getSocketDescriptor(), message, size_t(message));

    if (sendingStatus < 0)
        throw runtime_error(SENDING_ERROR);
}
