import socket

def receive_file(port,file_name):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((socket.gethostbyname(socket.gethostname()), port))
    server_socket.listen(1)

    print(f"Server listening on port {port}...")

    client_socket, client_address = server_socket.accept()
    print(f"Connection established with {client_address}")

    with open(file_name, 'wb') as file:
        data = client_socket.recv(1024)
        while data:
            file.write(data)
            data = client_socket.recv(1024)

    print(f"File received successfully from {client_address}")
    client_socket.close()
    server_socket.close()

if __name__ == "__main__":
    port = 5000  # You can use any available port
    file_name = "received_file2.txt"  # Change the file name as needed
    receive_file(port,file_name)
