import socket

SERVER_IP = '10.0.2.15'
SERVER_PORT = 12345
BUFFER_SIZE = 1024

def send_file_to_client(filename, client_address, server_socket):
    try:
        with open(filename, 'rb') as file:
            data = file.read(BUFFER_SIZE)
            while data:
                server_socket.sendto(data, client_address)
                data = file.read(BUFFER_SIZE)
        print(f"File '{filename}' sent to {client_address}")
    except FileNotFoundError:
        print(f"File '{filename}' not found.")

def multi_client(server_socket):
    print(f"Server listening on {SERVER_IP}:{SERVER_PORT}")

    while True:
        data, client_address = server_socket.recvfrom(BUFFER_SIZE)
        filename = data.decode('utf-8')
        send_file_to_client(filename, client_address, server_socket)

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind((SERVER_IP, SERVER_PORT))
    multi_client(server_socket)

if __name__ == "__main__":
    main()

