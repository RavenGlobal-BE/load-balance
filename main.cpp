#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <csignal>
#include <iostream>
#include "log.h"

using std::cout;
using std::endl;

int main() {
    log("You might want to check one this out", log_type::warning);
    log("Just letting you something know", log_type::info);
    log("Just verbose info to let you what's going on", log_type::debug);
    log("An error happened", log_type::error);

    signal(SIGPIPE, SIG_IGN);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    const int f = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, SOMAXCONN); //2nd Argument -> max_queue

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    log(buffer, log_type::debug);

    close(serverSocket);

    return 0;
}
