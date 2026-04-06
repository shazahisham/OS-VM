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
int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    name += "\n";

    send(clientSocket, name.c_str(), name.length(), 0);

    thread t(receiveMessages, clientSocket);

    string msg;
    while (true) {
        cout << "> ";
        getline(cin, msg);

        if (msg == "/quit") break;

        msg += "\n";
        send(clientSocket, msg.c_str(), msg.length(), 0);
    }

    close(clientSocket);
    return 0;
}