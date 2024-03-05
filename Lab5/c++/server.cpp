#include<iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = filesystem;
string directory = "./serverFiles/";
int main(){
    int serverSocket = socket(AF_INET,SOCK_DGRAM,0);
    if(serverSocket==-1){
        cout<<"Error creating server socket"<<endl;
        close(serverSocket);
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(3000);


    if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))==-1){
        cout<<"Error binding socket to server"<<endl;
        close(serverSocket);
        return -1;
    }

    cout<<"Server ready"<<endl;

    sockaddr_in clientAddress;
    socklen_t clientAddLen=sizeof(clientAddress);
    while(true){
        char buff[1024];
        ssize_t bytesRecieved = recvfrom(serverSocket,buff,sizeof(buff),0,(struct sockaddr*)&clientAddress,&clientAddLen);
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

                ssize_t bytesSend = sendto(serverSocket,fileContent,strlen(fileContent),0,(struct sockaddr*)&clientAddress,clientAddLen);
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
            ssize_t bytesSend = sendto(serverSocket,message,strlen(message),0,(struct sockaddr*)&clientAddress,clientAddLen);
            if(bytesSend==-1){
                cout<<"Error sending response message"<<endl;
            }
        }
    }

    close(serverSocket);
}