import socket
import os

def send_file(filename, conn):
    with open(filename, 'rb') as f:
        data = f.read(1024)
        while data:
            conn.send(data)
            data = f.read(1024)

def main():
    # Define host and port
    host = socket.gethostbyname(socket.gethostname())
    port = 9999

    # Create socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind to the address and port
    server_socket.bind((host, port))

    # Listen for incoming connections
    server_socket.listen(5)
    print("Server listening on port", port)

    while True:
        # Accept a connection
        conn, addr = server_socket.accept()
        print("Connection from:", addr)

        # Receive the filename from the client
        filename = conn.recv(1024).decode()
        print("File requested by client:", filename)

        # Check if the file exists
        if os.path.exists(filename):
            # Send the file to the client
            send_file(filename, conn)
            print("File sent successfully")
        else:
            print("File not found")

        # Close the connection
        conn.close()

if __name__ == "__main__":
    main()

