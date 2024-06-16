#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>
#include <arpa/inet.h>


#define SERVER_ADDR "127.0.0.1"
#define PORT 8080
#define SERVER_FILES_DIR "./serverFiles/"

using namespace std;

int main() {
    int server_socket=socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket==-1){
        cerr << "Socket creation error" << endl;
        close(server_socket);
        return -1;
    }
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        cerr << "Bind failed" << endl;
        close(server_socket);
        return -1;
    }

    if (listen(server_socket, 5) < 0) {
        cerr << "Listen failed" << endl;
        close(server_socket);
        return -1;
    }
    cout<<"Hey there!! , Server listening on 127.0.0.1:8080"<<endl;

    while (true) {
        if ((new_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            cerr << "Accept failed" << endl;
            close(server_socket);
            return -1;
        }

        int valread = read(new_socket, buffer, 1024);
        if (valread <= 0) {
            close(new_socket);
            continue;
        }

        string filePath = SERVER_FILES_DIR + string(buffer);

        ifstream file(filePath, ios::binary);
        if (!file.is_open()) {
            cout << "File not found: " << filePath << endl;

            int notFound = -1;
            send(new_socket, &notFound, sizeof(notFound), 0);

            close(new_socket);
            continue;
        }

        struct stat fileStat;
        if (stat(filePath.c_str(), &fileStat) < 0) {
            cout << "Error getting file size." << endl;
            close(new_socket);
            continue;
        }

        int fileSize = fileStat.st_size;
        send(new_socket, &fileSize, sizeof(fileSize), 0);

        char fileBuffer[1024];
        while (!file.eof()) {
            file.read(fileBuffer, sizeof(fileBuffer));
            send(new_socket, fileBuffer, file.gcount(), 0);
        }

        file.close();
        close(new_socket);
    }

    return 0;
}
