#include "tcpserver.h"
#include <iostream>

/**
 * @brief Main entry point for the server application.
 * @param argv Command-line argument such as port number.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    int port = std::stoi(argv[1]);
    TCPServer server(port);
    server.start();

    return EXIT_SUCCESS;
}
