#include "tcpserver.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

std::mutex log_mutex;

/**
 * @brief Logs a message to the log.txt file with thread safety.
 * @param message The message to log.
 */
void logMessage(const std::string &message) {
    std::lock_guard<std::mutex> guard(log_mutex);
    std::ofstream log_file("log.txt", std::ios_base::app);

    if (log_file.is_open()) {
        log_file << message << std::endl;
        log_file.close();
    }
}

/**
 * @brief Handles client connections and processes incoming messages.
 * @param client_socket The socket file descriptor for the client connection.
 */
void handleClient(const int client_socket) {
    char buffer[1024];
    int bytes_read;

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        time_t now = time(0);
        struct tm *ltm = localtime(&now);
        char timestamp[64];
        snprintf(timestamp, sizeof(timestamp), "[%d-%02d-%02d %02d:%02d:%02d.%03d] ",
                 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
                 ltm->tm_hour, ltm->tm_min, ltm->tm_sec, 0);
        logMessage(std::string(timestamp) + buffer);
    }

    close(client_socket);
}

TCPServer::TCPServer(const int port) : port_(port) {
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    if (bind(server_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket_);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket_, 5) == -1) {
        perror("listen");
        close(server_socket_);
        exit(EXIT_FAILURE);
    }
}

void TCPServer::start() const {
    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket_, (struct sockaddr*)&client_addr, &client_addr_len);

        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        std::thread client_thread(handleClient, client_socket);
        client_thread.detach();
    }
}

TCPServer::~TCPServer() {
    close(server_socket_);
}
