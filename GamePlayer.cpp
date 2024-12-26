#include <iostream>  
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main(){
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888); // Server port
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Server IP address

    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char buffer[1024] = {0};
    char message[1024] = {0};
 
    while(true){

        int bytesRecved = recv(clientSocket, buffer, sizeof(buffer), 0); //add timeout?
        cout << "Server: " << buffer << endl;
        cin.getline(message, 1024);
        
        if (string(message) == "quit"){
            break;
        }

        send(clientSocket, message, strlen(message), 0);


        memset(buffer, 0, sizeof(buffer));
        memset(message, 0, sizeof(message));

    }
    
    // Clean up
    closesocket(clientSocket);
    WSACleanup();

    return 0;


}

