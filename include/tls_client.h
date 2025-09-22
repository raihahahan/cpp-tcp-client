#pragma once
#include <string>
#include <memory>
#include <openssl/ssl.h>

// reference: 
// - https://wiki.openssl.org/index.php/SSL/TLS_Client
class TlsClient {
    struct SSL_CTX_deleter { 
        void operator()(SSL_CTX* ctx) const {
            SSL_CTX_free(ctx);
        }
    };

    struct SSL_deleter {
        void operator()(SSL* ssl) const {
            SSL_free(ssl);
        }
    };

    std::unique_ptr<SSL_CTX, SSL_CTX_deleter> ctx;
    std::unique_ptr<SSL, SSL_deleter> ssl;

public:
    explicit TlsClient(int fd);
    void write(const std::string& data);
    std::string read_all();
    void shutdown();
};