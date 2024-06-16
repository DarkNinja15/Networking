import socket

SERVER_IP = '10.0.2.15'
SERVER_PORT = 12345
BUFFER_SIZE = 1024

def receive_file_from_server(filename, client_socket):
    try:
        with open(filename, 'wb') as file:
            while True:
                data, server_address = client_socket.recvfrom(BUFFER_SIZE)
                if not data:
                    break
                file.write(data)
        print(f"File '{filename}' received from server.")
    except Exception as e:
        print(f"An error occurred: {e}")

def single_client(filename):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = (SERVER_IP, SERVER_PORT)
    client_socket.sendto(filename.encode('utf-8'), server_address)
    receive_file_from_server(filename, client_socket)
    client_socket.close()

def main():
    filename = input("Enter file name: ")
    single_client(filename)

if __name__ == "__main__":
    main()

