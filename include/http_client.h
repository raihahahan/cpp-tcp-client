#pragma once
#include <string>

class HttpClient {
    std::string host;
    uint16_t port;

public:
    HttpClient(const std::string& host, const uint16_t& port);
    std::string get(const std::string& path);
};