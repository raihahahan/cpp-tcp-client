#include "http_client.h"
#include "tcp_socket.h"
#include "tls_client.h"
#include <iostream>

HttpClient::HttpClient(const std::string& host, const uint16_t& port) : host{std::move(host)}, port{port} {};

std::string HttpClient::get(const std::string& path) {
    TcpSocket tcpSocket(host, port);
    TlsClient tlsClient(tcpSocket.get_fd());

    std::string request = 
        "GET " + path + " HTTP/1.1\r\n"
        "Host: " + host + "\r\n"
        "Connection: close\r\n\r\n";

    tlsClient.write(request);
    std::string response = tlsClient.read_all();
    tlsClient.shutdown();

    return response;
};

