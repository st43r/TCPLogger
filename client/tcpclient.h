#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>

/**
 * @class TCPClient
 * @brief A class to handle a TCP client that connects to a server and sends messages.
 */
class TCPClient {
public:
    /**
     * @brief Constructs a TCPClient object.
     * @param name The name of the client.
     * @param port The port number of the server to connect to.
     * @param interval The interval in seconds between sending messages.
     */
    TCPClient(std::string name, int port, int interval);

    /**
     * @brief Starts the client and sends messages to the server.
     */
    void start();

    /**
     * @brief Destroys the TCPClient object and closes the client socket.
     */
    ~TCPClient();

private:
    std::string name_; /**< The name of the client. */
    int port_; /**< The port number of the server. */
    int interval_; /**< The interval in seconds between sending messages. */
    int client_socket_; /**< The socket file descriptor for the client. */
};

#endif // TCPCLIENT_H
