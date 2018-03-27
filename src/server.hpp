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
    ClientObject* clients[QUEUE_SIZE];
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

    /**
     * @brief broadcastMessage
     * @param message
     * @param clientDescriptor The descriptor of client who send the message
     *
     * Broadcasts message to all the clients without the one with given clientDescriptor
     */
    void broadcastMessage(const char *message, const int &clientDescriptor) const;

    void handleOptionsInterface(ClientObject *client) const;
    void handleNickChanging(ClientObject* client) const;

    int putClientAtFirstFreeArraySpace(ClientObject *client);
public:
    Server(const int& portNumber);
    ~Server();
    /**
     * @brief runServer
     *
     * Method listens for new connections, accepts them and creates new thread for each new connection
     */
    void runServer();
    void eraseThreadOfNumber(const uint& threadNumber);


};

#endif // SERVER_H
