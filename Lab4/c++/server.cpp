#include<iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
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
            cout<<"Error recieving data"<<endl;
            continue;
        }
        buff[bytesRecieved]='\0';
        cout<<"Data recieved successfully"<<endl;
        cout<<buff<<endl;

        char message[1024];
        cout<<"Enter message to sent to client"<<endl;
        cin.getline(message,sizeof(message));

        ssize_t bytesSent=sendto(serverSocket,message,strlen(message),0,(struct sockaddr*)&clientAddress,clientAddLen);

        if(bytesSent==-1){
            cout<<"Error sending message"<<endl;
            continue;
        }

        cout<<"Data sent successfully"<<endl;

    }

    close(serverSocket);
}