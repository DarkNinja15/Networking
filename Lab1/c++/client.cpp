#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
using namespace std;

int main(){
    int clientSocket=socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket==-1){
        cout<<"Error creating socket"<<endl;
        close(clientSocket);
        return 1;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(8080);

    if(connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))==-1){
        cout<<"Error connecting to server"<<endl;
        close(clientSocket);
        return 1;
    }

    cout<<"Connected to server..."<<endl;
    while(true){
        cout<<"Enter your message: "<<endl;
        char message[1024];
        cin.getline(message,sizeof(message));
        ssize_t bytesSent=send(clientSocket,message,strlen(message),0);
        if(bytesSent==-1){
            cout<<"Error sending message"<<endl;
            close(clientSocket);
            return 1;
        }
        else{
            cout<<"Message sent successfully"<<endl;
            cout<<"[Client]: "<<message<<endl;
        }

        char buff[1024];
        ssize_t bytesRecieved=recv(clientSocket,buff,sizeof(buff),0);
        if(bytesRecieved==-1){
            cout<<"Error recieving data"<<endl;
            close(clientSocket);
            return 1;
        }
        else{
            buff[bytesRecieved]='\0';
            cout<<"[Server]: "<<buff<<endl;
        }
    }
    close(clientSocket);
}