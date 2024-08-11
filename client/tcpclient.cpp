#include "tcpclient.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <ctime>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

TCPClient::TCPClient(std::string name, int port, int interval)
    : name_(std::move(name)), port_(port), interval_(interval) {
    client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_ == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(client_socket_);
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(client_socket_);
        exit(EXIT_FAILURE);
    }
}

void TCPClient::start() {
    while (true) {
        time_t now = time(0);
        struct tm *ltm = localtime(&now);

        char timestamp[64];
        snprintf(timestamp, sizeof(timestamp), "[%d-%02d-%02d %02d:%02d:%02d.%03d] ",
                 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
                 ltm->tm_hour, ltm->tm_min, ltm->tm_sec, 0);

        std::string message = std::string(timestamp) + name_;
        send(client_socket_, message.c_str(), message.size(), 0);
        std::this_thread::sleep_for(std::chrono::seconds(interval_));
    }
}

TCPClient::~TCPClient() {
    close(client_socket_);
}
