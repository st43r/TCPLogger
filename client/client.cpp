#include "tcpclient.h"
#include <iostream>

/**
 * @brief Main entry point for the client application.
 * @param argv Command-line arguments such as name port and interval.
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <name> <port> <interval>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string name = argv[1];
    int port = std::stoi(argv[2]);
    int interval = std::stoi(argv[3]);
    TCPClient client(name, port, interval);
    client.start();

    return EXIT_SUCCESS;
}
