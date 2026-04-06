#include <iostream>
#include <thread>
#include <string>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
void receiveMessages(int sock) {
    char buffer[1024];

    while (true) {
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0) {
            cout << "\nDisconnected from server.\n";
            break;
        }

        buffer[bytes] = '\0';
        cout << "\n" << buffer;
        cout << "> ";
    }
}