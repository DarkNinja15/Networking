#include<iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
int main(){
    int clientSocket = socket(AF_INET,SOCK_DGRAM,0);
    if(clientSocket==-1){
        cout<<"Error creating server socket"<<endl;
        close(clientSocket);
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(3000);

    socklen_t serverAddLen=sizeof(serverAddress);

    while(true){

        char message[1024];
        cout<<"Enter message to sent to server"<<endl;
        cin.getline(message,sizeof(message));

        ssize_t bytesSent=sendto(clientSocket,message,strlen(message),0,(struct sockaddr*)&serverAddress,serverAddLen);

        if(bytesSent==-1){
            cout<<"Error sending message"<<endl;
            continue;
        }

        cout<<"Data sent successfully"<<endl;

        char buff[1024];
        ssize_t bytesRecieved = recvfrom(clientSocket,buff,sizeof(buff),0,(struct sockaddr*)&serverAddress,&serverAddLen);
        if(bytesRecieved==-1){
            cout<<"Error recieving data"<<endl;
            continue;
        }
        buff[bytesRecieved]='\0';
        cout<<"Data recieved successfully"<<endl;
        cout<<buff<<endl;
    }
}