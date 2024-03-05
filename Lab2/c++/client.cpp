#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

char *getFileName()
{
    cout << "Enter the file name : " << endl;
    char input[1024];
    cin.getline(input, sizeof(input));
    char *fileName = input;
    return fileName;
}

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        cout << "Error creating client socket" << endl;
        close(clientSocket);
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(5000);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        cout << "Error connecting to server" << endl;
        close(clientSocket);
        return -1;
    }

    cout << "Connected to server" << endl;

    while (true)
    {
        char *fileName = getFileName();
        cout << "fileName" << fileName << endl;
        ssize_t bytesSend = send(clientSocket, fileName, strlen(fileName), 0);
        if (bytesSend == -1)
        {
            cout << "Error requesting file" << endl;
            continue;
        }
        cout << "File requested : " << fileName << endl;
        char buff[1024];
        ssize_t bytesRecieved = recv(clientSocket, buff, sizeof(buff), 0);
        if (bytesRecieved == -1)
        {
            cout << "Error recieving file" << endl;
            continue;
        }
        if(buff[0]=='-'){
            cout<<"File is not available at the moment"<<endl;
            continue;
        }
        const char *path = "./clientFiles/";
        char *fullPath = (char *)malloc(strlen(path) + strlen(fileName) + 1);
        if (fullPath == NULL)
        {
            perror("Memory allocation failed");
            return 1;
        }
        strcpy(fullPath, path);
        strcat(fullPath, fileName);
        cout << "filePath :" << fullPath << endl;
        buff[bytesRecieved] = '\0';
        FILE *fd = fopen(fullPath, "wb");
        if (fd == NULL)
        {
            cout << "Error opening file" << endl;
        }
        else
        {
            fwrite(&buff, 1, bytesRecieved, fd);
            fclose(fd);
        }
    }

    close(clientSocket);
}