#include "http_client.h"
#include <iostream>
#include <regex>

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

int main() {
    constexpr const char* HOST = "varlabs.comp.nus.edu.sg";
    constexpr const char* PATH = "/tools/yourip.php";
    constexpr uint16_t PORT = 443;
    HttpClient client(HOST, PORT);
    std::string response = client.get(PATH);
    response = parse(response);
    std::string result = "My public IP address is " + response;
    std::cout << result << std::endl;
    return 0;
}