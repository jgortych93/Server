#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

class Client
{
    int fileDescriptor;
    int port;
    struct sockaddr_in address;
    void initializeNewSocket();
    /**
     * @brief fillServerAddressStruct
     *
     * Fills serverAddress struct with all data needed for proper comunication
     */
    void fillServerAddressStruct();
    void bindSocket();
    void listenOnSocket();
    void startClient();

public:
        Client(const int& port);


}

#endif //CLIENT_H
