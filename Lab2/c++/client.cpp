#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/stat.h>

#define PORT 8080
#define SERVER_ADDR "127.0.0.1"
#define CLIENT_FILES_DIR "./clientFiles/"

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1){
        cerr << "Socket creation error" << endl;
        close(sock);
        return -1;
    }
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serv_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection failed" << endl;
        close(sock);
        return -1;
    }

    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    send(sock, fileName.c_str(), fileName.length(), 0);

    int fileSize;
    recv(sock, &fileSize, sizeof(fileSize), 0);

    if (fileSize == -1) {
        cout << "File not found on server." << endl;
        close(sock);
        return -1;
    }

    string filePath = CLIENT_FILES_DIR + fileName;
    ofstream outFile(filePath, ios::binary);

    if (!outFile.is_open()) {
        cerr << "Failed to create file" << endl;
        close(sock);
        return -1;
    }

    int bytesRead;
    char fileBuffer[1024];
    while (fileSize > 0) {
        bytesRead = recv(sock, fileBuffer, sizeof(fileBuffer), 0);
        outFile.write(fileBuffer, bytesRead);
        fileSize -= bytesRead;
    }

    outFile.close();
    cout << "File received successfully." << endl;

    close(sock);

    return 0;
}
