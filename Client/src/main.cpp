#include <iostream>
#include "Client.hpp"

#define IP_ADDRESS "127.0.0.1"
#define PORT 8080

using namespace std;

int main()
{
    Client client(IP_ADDRESS, PORT);

    client.connectToServer();

    client.communicateWithServer();

    return 0;
}
