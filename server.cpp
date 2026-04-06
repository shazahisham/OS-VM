#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <algorithm>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

vector<int> clients;
mutex clientsMutex;
void broadcastMessage(const string& message, int senderSocket) {
    lock_guard<mutex> lock(clientsMutex);

    for (int client : clients) {
        if (client != senderSocket) {
            send(client, message.c_str(), message.length(), 0);
        }
    }
}

void handleClient(int clientSocket) {
    char buffer[1024];
    string clientName;

    int nameBytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (nameBytes <= 0) {
        close(clientSocket);
        return;
    }

    buffer[nameBytes] = '\0';
    clientName = buffer;

    string joinMsg = clientName + " joined the chat.\n";
    cout << joinMsg;
    broadcastMessage(joinMsg, clientSocket);

    while (true) {
        int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0) break;

        buffer[bytes] = '\0';
        string msg = clientName + ": " + buffer;

        cout << msg;
        broadcastMessage(msg, clientSocket);
    }

    {
        lock_guard<mutex> lock(clientsMutex);
        clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
    }

    string leaveMsg = clientName + " left the chat.\n";
    cout << leaveMsg;
    broadcastMessage(leaveMsg, clientSocket);

    close(clientSocket);
}
int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    cout << "Server running on port 54000...\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        {
            lock_guard<mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
        }

        thread t(handleClient, clientSocket);
        t.detach();
    }

    close(serverSocket);
    return 0;
}