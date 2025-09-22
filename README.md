# Simple C++ TCP Client with SSL wrapper using OpenSSL

## 1. Demo

The demo program is to retrieve my public IP address, but this can be used for any TCP request over SSL

[Go to demo](./demo.mov)

## 2. Installation

- Note: this has only been tested on Mac M2

```
make all
./client
```

## 3. Explanation

**1) Project structure**
(made with https://marketplace.visualstudio.com/items?itemName=jmkrivocapich.drawfolderstructure)

```
└── 📁cpp-tcp-client
    └── 📁include
        ├── http_client.h
        ├── tcp_socket.h
        ├── tls_client.h
    └── 📁src
        ├── http_client.cpp
        ├── main.cpp
        ├── tcp_socket.cpp
        ├── tls_client.cpp
    ├── Makefile
```

**2) How it works**

1. Resolve host: get IP from hostname (`gethostbyname`)
2. Open TCP socket: `socket()` + `connect()` to server:443
3. Start TLS: wrap socket with OpenSSL (`SSL_connect`)
4. Send HTTP request: `SSL_write("GET ...")`
5. Receive response: `SSL_read()` until done
6. Parse body: extract the data
7. Cleanup: shutdown TLS, free SSL, close socket

## 4. References

- https://man7.org/linux/man-pages/man3/gethostbyname.3.html
- https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/
- https://wiki.openssl.org/index.php/SSL/TLS_Client
- https://www.ibm.com/docs/en/ztpf/1.1.2024?topic=apis-tls-client-method
- https://www.ibm.com/docs/en/ztpf/1.1.2024?topic=layer-ssl-examples
