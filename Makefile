CXX = g++
CXXFLAGS = -Wall -std=c++20 -Iinclude
TARGET = client

SRC = src/main.cpp src/http_client.cpp src/tcp_socket.cpp src/tls_client.cpp

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LIBS = -lssl -lcrypto
endif

ifeq ($(UNAME_S),Darwin)
    OPENSSL_PATH = $(shell brew --prefix openssl)
    CXXFLAGS += -I$(OPENSSL_PATH)/include
    LIBS = -L$(OPENSSL_PATH)/lib -lssl -lcrypto
endif

ifeq ($(OS),Windows_NT)
    LIBS = -lssl -lcrypto -lws2_32
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET) $(TARGET).exe
