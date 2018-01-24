#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

class Client
{
    const char* ipAddress;
    int serverFileDescriptor;
    int clientFileDescriptor;
    int serverPort;
    struct sockaddr_in serverAddress;

    void initializeNewSocket();
    /**
     * @brief fillServerAddressStruct
     *
     * Fills serverAddress struct with all data needed for proper comunication
     */
    void fillServerAddressStruct();
    /**
     * @brief resolveAddress
     *
     * Assigns ip address as server's address in the proper way.
     */
    void resolveAddress();

    void readMessage(char* buffer) const;
    void sendMessage(const char* message) const;

    void connectToServer();

    void communicateWithServer();

public:
        Client(const char* ipAddress, const int& serverPort);



};

#endif //CLIENT_H
