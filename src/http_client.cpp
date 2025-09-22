#include "http_client.h"
#include "tcp_socket.h"
#include "tls_client.h"
#include <regex>
#include <iostream>

std::string parse(std::string& response) {
    auto pos = response.find("\r\n\r\n");
    response = (pos != std::string::npos) ? response.substr(pos + 4) : response;
    std::regex ip_regex(R"((\d{1,3}\.){3}\d{1,3})");
    std::smatch match;
    if (std::regex_search(response, match, ip_regex)) {
        return match.str();
    } else {
        std::cerr << "Could not parse regex\n";
        return "";
    }
}

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
    response = parse(response);
    tlsClient.shutdown();

    return response;
};

