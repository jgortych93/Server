#ifndef CLIENTOBJECT_H
#define CLIENTOBJECT_H
#include <netinet/in.h>

/**
 * @brief The ClientObject class
 * Representation of single chat client
 */
class ClientObject
{
    struct sockaddr_in clientAddress;	/// Client remote address
    int connectionDesc;                 /// Connection file descriptor
    uint userId;                         /// Client unique identifier
    char name[32];                      /// Client name
public:
    void setUserId(const uint& id) {this->userId = id;}
    void setConnectionDesc(const int& connDesc) {this->connectionDesc = connDesc;}
};

#endif //CLIENTOBJECT_H
