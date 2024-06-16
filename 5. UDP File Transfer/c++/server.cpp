#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>

#define PORT 8080
#define SERVER_FILES_DIR "./serverFiles/"

using namespace std;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];

    // memset(&servaddr, 0, sizeof(servaddr));
    // memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        cerr<<"bind failed"<<endl;
        close(sockfd);
        return -1;
    }

    int len, n;
    len = sizeof(cliaddr);

    while (true) {
        n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&cliaddr, (socklen_t*)&len);
        buffer[n] = '\0';

        string filePath = SERVER_FILES_DIR + string(buffer);

        ifstream file(filePath, ios::binary);
        if (!file.is_open()) {
            cout << "File not found: " << filePath << endl;
            
            sendto(sockfd, "-1", 2, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
            continue;
        }

        struct stat fileStat;
        if (stat(filePath.c_str(), &fileStat) < 0) {
            cout << "Error getting file size." << endl;
            continue;
        }

        int fileSize = fileStat.st_size;
        sendto(sockfd, &fileSize, sizeof(fileSize), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);

        char fileBuffer[1024];
        while (!file.eof()) {
            file.read(fileBuffer, sizeof(fileBuffer));
            sendto(sockfd, fileBuffer, file.gcount(), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        }

        file.close();
    }

    return 0;
}
