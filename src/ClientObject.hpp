#ifndef CLIENTOBJECT_H
#define CLIENTOBJECT_H
#include <netinet/in.h>

#define NAME_SIZE 32

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
    char* name = new char[NAME_SIZE+1];                      /// Client name
public:
    void setName(const char* name) {this->name = const_cast<char*>(name);}
    char* getName() const {return this->name;}
    void setUserId(const uint& id) {this->userId = id;}
    void setConnectionDesc(const int& connDesc) {this->connectionDesc = connDesc;}
    /**
     * @brief sendMessage
     * @param message A message to sent
     *
     * Function sends passed message to the client and throws exception in case of sending failure
     */
    void sendMessage(const char* message) const;
    int getSocketDescriptor() const {return this->connectionDesc;}
    void setClientAddress(const struct sockaddr_in& address){this->clientAddress = address;}
};

#endif //CLIENTOBJECT_H
