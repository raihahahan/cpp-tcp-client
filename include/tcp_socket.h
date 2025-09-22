#pragma once
#include <string>

class TcpSocket {
    int fd;

public:
    TcpSocket(const std::string& hostname, const uint16_t& port);
    int get_fd() const;
    ~TcpSocket();

    // disable copy
    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator=(const TcpSocket&) = delete;
};