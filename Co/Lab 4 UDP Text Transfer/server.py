import socket

SERVER_IP = socket.gethostbyname(socket.gethostname())
SERVER_PORT = 8888

def multi_client():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind((SERVER_IP, SERVER_PORT))
    print(f"Server listening on {SERVER_IP}:{SERVER_PORT}")

    while True:
        data, client_address = server_socket.recvfrom(1024)
        print(f"Received from {client_address}: {data.decode('utf-8')}")
        message = input("Enter your message: ")
        server_socket.sendto(message.encode('utf-8'), client_address)

def main():
    multi_client()

if __name__ == "__main__":
    main()

