#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;
string directory = "./serverFiles/";

int main(){
    int serverSocket = socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket==-1){
        cout<<"Error creating server"<<endl;
        close(serverSocket);
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(5000);

    if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))==-1){
        cout<<"Error binding socket to ip"<<endl;
        close(serverSocket);
        return -1;
    }
    
    if(listen(serverSocket,10)==-1){
        cout<<"Error listening server socket"<<endl;
        close(serverSocket);
        return -1;
    }

    cout<<"Server listening on 127.0.0.1:5000"<<endl;

    sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    int clientSocket = accept(serverSocket,(struct sockaddr*)&clientSocket,&clientAddressLen);
    if(clientSocket==-1){
        cout<<"Error creating client socket"<<endl;
        close(serverSocket);
        close(clientSocket);
        return -1;
    }

    cout<<"Connection accepted from "<<inet_ntoa(clientAddress.sin_addr)<<endl;


    while(true){
        char buff[1024];
        ssize_t bytesRecieved = recv(clientSocket,buff,sizeof(buff),0);
        if(bytesRecieved==-1){
            cout<<"Error recieving fileName"<<endl;
            continue;
        }
        buff[bytesRecieved]='\0';
        cout<<"File requested : "<<buff<<endl;
        string filePath = directory+buff;
        if(fs::exists(filePath)){
            ifstream inputFile(filePath,ios::binary);
            if(inputFile.is_open()){
                inputFile.seekg(0,ios::end);
                streampos fileSize=inputFile.tellg();
                inputFile.seekg(0,ios::beg);

                char *fileContent = new char[static_cast<size_t>(fileSize)];

                inputFile.read(fileContent,fileSize);
                inputFile.close();

                ssize_t bytesSend = send(clientSocket,fileContent,fileSize,0);
                if(bytesSend==-1){
                    cout<<"Error sending file"<<endl;
                }
                else{
                    cout<<"File sent successfully"<<endl;
                }

                delete [] fileContent;
            }
        }
        else{
            char message[1024] = "-1";
            ssize_t bytesSend = send(clientSocket,message,strlen(message),0);
            if(bytesSend==-1){
                cout<<"Error sending response message"<<endl;
            }
        }
    }

    close(serverSocket);
    close(clientSocket);

}