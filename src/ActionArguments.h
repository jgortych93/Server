#ifndef ACTION_ARGUMENTS_H
#define ACTION_ARGUMENTS_H

#include "ClientObject.hpp"
#include "server.hpp"

/**
 * @brief The ActionArguments struct
 *
 * Stores the current client and server instances for passing it to action() function
 * which is the action taken by each new client thread
 */
typedef struct ActionArguments
{
    ClientObject client;
    Server* server;

    ActionArguments(const ClientObject& clientObject, Server* server):client(clientObject), server(server){}

}ActionArguments;

#endif
