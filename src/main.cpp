#include "http_client.h"
#include <iostream>

int main() {
    constexpr const char* HOST = "varlabs.comp.nus.edu.sg";
    constexpr const char* PATH = "/tools/yourip.php";
    constexpr uint16_t PORT = 443;
    HttpClient client(HOST, PORT);
    std::string response = client.get(PATH);
    std::string result = "My public IP address is " + response;
    std::cout << result << std::endl;
    return 0;
}