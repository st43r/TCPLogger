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
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        struct tm ltm{};
        localtime_r(&now_time, &ltm);
        int ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                     now.time_since_epoch())
                     .count() %
                 1000;

        char timestamp[64];
        snprintf(timestamp, sizeof(timestamp),
                 "[%d-%02d-%02d %02d:%02d:%02d.%03d] ",
                 1900 + ltm.tm_year, 1 + ltm.tm_mon, ltm.tm_mday, ltm.tm_hour,
                 ltm.tm_min, ltm.tm_sec, ms);

        std::string message = std::string(timestamp) + name_;
        send(client_socket_, message.c_str(), message.size(), 0);
        std::this_thread::sleep_for(std::chrono::seconds(interval_));
    }
}

TCPClient::~TCPClient() {
    close(client_socket_);
}
