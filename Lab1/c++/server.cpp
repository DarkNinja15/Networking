#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
using namespace std;

int main(){
    int serverSocket=socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket==-1){
        cout<<"Error creating socket"<<endl;
        close(serverSocket);
        return 1;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.01");
    serverAddress.sin_port=htons(8080);

    if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))==-1){
        cout<<"Error binding socket"<<endl;
        close(serverSocket);
        return 1;
    }

    if(listen(serverSocket,10)==-1){
        cout<<"Error listening server"<<endl;
        close(serverSocket);
        return 1;
    }

    cout<<"Hey there!! , Server listening on 127.0.0.1:8080"<<endl;
    sockaddr_in clientAddress;
        socklen_t clientAddressLen=sizeof(clientAddress);
        int clientSocket=accept(serverSocket,(struct sockaddr*)&clientAddress,&clientAddressLen);
        if(clientSocket==-1){
            cout<<"Error connecting to client"<<endl;
            close(serverSocket);
            close(clientSocket);
            return 1;
        }

        cout<<"Connection accepted from "<<inet_ntoa(clientAddress.sin_addr)<<endl;

    while(true){
        char buff[1024];
        ssize_t bytesRead=recv(clientSocket,buff,sizeof(buff),0);
        if(bytesRead==-1){
            cout<<"Error recieving data"<<endl;
            close(serverSocket);
            close(clientSocket);
            return 1;
        }
        else{
            buff[bytesRead]='\0';
            cout<<"Data fetched successfully"<<endl;
            cout<<"[Client]: "<<buff<<endl;
        }

        cout<<"Enter message to sent to client: "<<endl;
        char response[1024];
        cin.getline(response,sizeof(response));
        ssize_t bytesSent=send(clientSocket,response,strlen(response),0);
        if(bytesSent==-1){
            cout<<"Error sending response"<<endl;
        }
        else{
            cout<<"[Server]: "<<response<<endl;
        }
    }
    close(clientSocket);
    close(serverSocket);

}