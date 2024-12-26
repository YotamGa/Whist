#include <iostream>  
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include "DeckOfCards.h"
#include <map>
#include <vector>
#include <string>
using namespace std;
#pragma comment(lib, "ws2_32.lib")


void handleClient(SOCKET clientSocket, map<int, Game>& myGames, map<string, Player>& myPlayers){
    char buffer[1024] = {0};
    int bytesReceived;

    cout << "Client connected. Thread ID: " << this_thread::get_id() << endl;

    // Communicate with the client
    const char* welcomeMsg = "Welcome, enter your name: ";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        cout << "Received: " << buffer << endl;
        if(string(buffer) == "next"){
            const char* msg = "Enter next thing: ";
            send(clientSocket, msg, strlen(msg), 0);
        }
        memset(buffer, 0, sizeof(buffer));
    }
    if (bytesReceived == 0) {
        cout << "Client disconnected." << endl;
    } else {
        cerr << "recv() failed: " << WSAGetLastError() << endl;
    }

    closesocket(clientSocket);
}
string* parseCommand(string command){
    
}
// void doCommand(array<char,1024>& command){

// }


int main(){
    map<int, Game> myGames;
    map<string, Player> myPlayers;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed: " << WSAGetLastError() << endl;
    return 1;
    }
    cout << "1";
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSock == INVALID_SOCKET) {
        cerr << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    cout << "2";
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8888);
    if (bind(serverSock, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        cerr << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Listen failed: " << WSAGetLastError() << endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }
    cout << "Server is listening on port 8888..." << endl;




    while (true) {
        SOCKET clientSocket = accept(serverSock, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Accept failed: " << WSAGetLastError() << endl;
            continue;
        }

        thread clientThread(handleClient, clientSocket, ref(myGames), ref(myPlayers));
        clientThread.detach(); // Let the thread run independently
    }

}

