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

    void readMessage(char *buffer) const;
    static void sendMessage(const char* message, const int& serverDesc);

    /**
     * @brief handleTextEntering
     * @param attrs optionable arguments
     * @return return nothing
     *
     *Saves single chars to the buffer and sends message from the buffer when 'enter' key is pressed.
     */
    static void* handleTextEntering(void *attr);

public:
        Client(const char* ipAddress, const int& serverPort);

        void connectToServer() __attribute__((noreturn));

        void communicateWithServer() __attribute__ ((noreturn));



};

#endif //CLIENT_H
