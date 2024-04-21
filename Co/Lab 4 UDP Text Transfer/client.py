import socket

SERVER_IP = socket.gethostbyname(socket.gethostname())
SERVER_PORT = 8888

def single_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = (SERVER_IP, SERVER_PORT)

    while True:
        message = input("Enter your message: ")
        client_socket.sendto(message.encode('utf-8'), server_address)
        data, server = client_socket.recvfrom(1024)
        print(f"Received from server: {data.decode('utf-8')}")

def main():
    single_client()

if __name__ == "__main__":
    main()

