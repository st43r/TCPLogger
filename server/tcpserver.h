#ifndef TCPSERVER_H
#define TCPSERVER_H

/**
 * @class TCPServer
 * @brief A class to handle a TCP server that listens for client connections and processes messages.
 */
class TCPServer {
public:
    /**
     * @brief Constructs a TCPServer object.
     * @param port The port number on which the server will listen.
     */
    explicit TCPServer(int port);

    /**
     * @brief Starts the server to listen for and handle client connections.
     */
    void start() const;

    /**
     * @brief Destroys the TCPServer object and closes the server socket.
     */
    ~TCPServer();

private:
    int port_; /**< The port number for the server. */
    int server_socket_; /**< The socket file descriptor for the server. */
};

#endif // TCPSERVER_H
