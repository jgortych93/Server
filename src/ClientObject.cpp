#include "ClientObject.hpp"
#include <unistd.h>
#include <stdexcept>

#define SENDING_ERROR "Sending to client has failed"

using namespace std;

void ClientObject::sendMessage(const char *message) const
{
    const int sendingStatus =  static_cast<const int>(write(this->getSocketDescriptor(), message, sizeof(message)));

    if (sendingStatus < 0)
        throw runtime_error(SENDING_ERROR);
}
