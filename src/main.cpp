#include <stdio.h>
#include "server.hpp"

int main()
{

    Server server(8081);
    server.runServer();

    return 0;
}
