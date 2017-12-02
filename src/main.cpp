#include <stdio.h>
#include "server.hpp"

int main()
{
    Server server(8080);
    server.runServer();

    return 0;
}
