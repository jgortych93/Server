#ifndef CLIENTOBJECT_H
#define CLIENTOBJECT_H
#include <netinet/in.h>

/**
 * @brief The ClientObject class
 *
 * Representation of single chat client
 */
class ClientObject
{
    struct sockaddr_in clientAddress;	/// Client remote address
    int connectionDesc;                 /// Connection file descriptor
    uint userId;                        /// Client unique identifier
    char name[32];                      /// Client name
    int getSocketDescriptor() const {return this->connectionDesc;}
public:
    void setName(const char* name) {this->name[0] = *name;}
    void setUserId(const uint& id) {this->userId = id;}
    void setConnectionDesc(const int& connDesc) {this->connectionDesc = connDesc;}
    /**
     * @brief sendMessage
     * @param message A message to sent
     *
     * Function sends passed message to the client and throws exception in case of sending failure
     */
    void sendMessage(const char* message) const;
};

#endif //CLIENTOBJECT_H
