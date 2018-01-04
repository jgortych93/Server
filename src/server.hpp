#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "ClientObject.hpp"


#define QUEUE_SIZE 5

class Server
{
    int socketDescriptor;
    int portNumber;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    pthread_t clientThreads[QUEUE_SIZE];
    static uint numberOfThreads;


    void initializeNewSocket();
    void fillServerAddressStruct();
    void bindSocket();
    void listenOnSocket();
    static void* action(void* clientDesc);
public:
    Server(const int& portNumber);

    void runServer();



};

#endif // SERVER_H
