import socket
import os

def receive_file(conn, filename):
    with open(filename, 'wb') as f:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            f.write(data)

def main():
    # Define host and port
    host = socket.gethostbyname(socket.gethostname())
    port = 9999

    # Create socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    client_socket.connect((host, port))
    print("Connected to server")

    # Get the filename from user input
    filename = input("Enter the filename you want to receive: ")

    # Send filename to server
    client_socket.send(filename.encode())

    # Receive file from server
    receive_file(client_socket, filename)
    print("File received successfully")

    # Close the connection
    client_socket.close()

if __name__ == "__main__":
    main()

