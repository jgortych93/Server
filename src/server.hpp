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
    /**
     * @brief fillServerAddressStruct
     *
     * Fills serverAddress struct with all data needed for proper comunication
     */
    void fillServerAddressStruct();
    void bindSocket();
    void listenOnSocket();
    /**
     * @brief action
     * @param clientDesc Client socket file descriptor
     * @return
     *
     * Standard action that new client thread executes. It creates new ClientObject instance and sends initial message
     */
    static void* action(void* clientDesc);
public:
    Server(const int& portNumber);
    /**
     * @brief runServer
     *
     * Method listens for new connections, accepts them and creates new thread for each new connection
     */
    void runServer();



};

#endif // SERVER_H
