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
    char* name;                      /// Client name
    uint8_t threadNumber;            /// Number of thread
public:
    ClientObject(){this->name = new char[NAME_SIZE+1]; }
    ClientObject(const int& descriptor, const struct sockaddr_in& address);

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

    int getConnectionDesc() const {return this->connectionDesc;}
    void setClientAddress(const struct sockaddr_in& address){this->clientAddress = address;}

    uint8_t getThreadNumber() const;
    void setThreadNumber(const uint8_t &value);
};

#endif //CLIENTOBJECT_H
