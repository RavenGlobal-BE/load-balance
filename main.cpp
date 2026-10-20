#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <csignal>
#include <iostream>
#include <string>
#include "log.h"

using std::cout;
using std::endl;

int main() {
    int amount = 0;
    constexpr int port = 8080;

    signal(SIGPIPE, SIG_IGN);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        log(strerror(errno), log_type::error);
    }
    listen(serverSocket, SOMAXCONN); //2nd Argument -> max_queue

    log("Ready to start serving requests on port: " + std::to_string(port), log_type::info);
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            continue;
        }
        char buffer[1024] = {0}; // A given request can be max 1 KB.
        size_t n = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (n > 0) {
            buffer[n] = '\0';
            ++amount;
            log(std::to_string(amount), log_type::debug);
        }
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}
