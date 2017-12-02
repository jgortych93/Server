#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

class Server
{
    int socketDescriptor;
    int portNumber;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    void initializeNewSocket();
    void fillServerAddressStruct();
public:
    Server(const int& portNumber);

    void runServer();



};

#endif // SERVER_H
