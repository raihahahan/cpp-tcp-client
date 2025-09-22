#include "tls_client.h"
#include <stdexcept>
#include <vector>
#include <openssl/err.h>
#include <iostream>

inline void throw_if(bool cond, const std::string& msg) {
    if (cond) throw std::runtime_error(msg);
}

// reference: 
// - https://wiki.openssl.org/index.php/SSL/TLS_Client
// - https://www.ibm.com/docs/en/ztpf/1.1.2024?topic=apis-tls-client-method
// - https://www.ibm.com/docs/en/ztpf/1.1.2024?topic=layer-ssl-examples
TlsClient::TlsClient(int fd) {
    SSL_library_init();
    SSL_load_error_strings();
    const SSL_METHOD* method = TLS_client_method();

    // set tls context to be tls client
    ctx.reset(SSL_CTX_new(method));
    throw_if(!ctx, "SSL_CTX_new failed");

    // set SSL connection with new context
    ssl.reset(SSL_new(ctx.get()));
    throw_if(!ssl, "SSL_new failed");
    
    // wrap the tcp socket fd
    SSL_set_fd(ssl.get(), fd);
    if (SSL_connect(ssl.get()) <= 0) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("SSL_connect failed");
    }
}

void TlsClient::write(const std::string& data) {
    SSL_write(ssl.get(), data.c_str(), static_cast<int>(data.size()));
}

void TlsClient::shutdown() {
    if (ssl) SSL_shutdown(ssl.get());
}

std::string TlsClient::read_all() {
    std::string result;
    std::vector<char> buf(4096);
    for (;;) {
        int n = SSL_read(ssl.get(), buf.data(), static_cast<int>(buf.size()));
        if (n <= 0) break;
        result.append(buf.data(), n);
    }

    return result;
}
