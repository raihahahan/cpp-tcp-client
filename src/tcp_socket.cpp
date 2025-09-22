#include "tcp_socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

// references:
// - https://man7.org/linux/man-pages/man3/gethostbyname.3.html
// - https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/
TcpSocket::TcpSocket(const std::string& hostname, const uint16_t& port) : fd{socket(AF_INET, SOCK_STREAM, 0)} {
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    hostent* host = gethostbyname(hostname.c_str());
    if (host == nullptr) {
        perror("gethostbyname");
        exit(1);
    }
    memcpy(&serverAddress.sin_addr, host->h_addr, host->h_length);
    connect(fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

int TcpSocket::get_fd() const {
    return fd;
}

TcpSocket::~TcpSocket() {
    if (fd >= 0) ::close(fd);
}