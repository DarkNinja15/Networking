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
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        cerr << "socket creation failed" << endl;
        close(sockfd);
        return -1;
    }
    struct sockaddr_in servaddr;
    char buffer[1024];
    
    // memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    sendto(sockfd, fileName.c_str(), fileName.length(), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    int n, len = sizeof(servaddr);
    n = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&servaddr, (socklen_t*)&len);
    buffer[n] = '\0';

    int fileSize;
    if (n == 2 && strncmp(buffer, "-1", 2) == 0) {
        cout << "File not found on server." << endl;
        close(sockfd);
        return -1;
    } else {
        memcpy(&fileSize, buffer, sizeof(int));
    }

    string filePath = CLIENT_FILES_DIR + fileName;
    ofstream outFile(filePath, ios::binary);

    if (!outFile.is_open()) {
        cerr << "Failed to create file" << endl;
        return -1;
    }

    char fileBuffer[1024];
    while (fileSize > 0) {
        n = recvfrom(sockfd, fileBuffer, sizeof(fileBuffer), MSG_WAITALL, (struct sockaddr *)&servaddr, (socklen_t*)&len);
        outFile.write(fileBuffer, n);
        fileSize -= n;
    }

    outFile.close();
    cout << "File received successfully." << endl;

    close(sockfd);

    return 0;
}
