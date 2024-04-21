import socket

def send_file(server_ip, port, file_name):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_ip, port))

    print(f"Connected to server at {server_ip}:{port}")

    with open(file_name, 'rb') as file:
        data = file.read(1024)
        while data:
            client_socket.send(data)
            data = file.read(1024)

    print(f"File sent successfully to server at {server_ip}:{port}")
    client_socket.close()

if __name__ == "__main__":
    server_ip = socket.gethostbyname(socket.gethostname())  # Replace with the IP address of your server
    port = 5000 # Make sure it matches the server's port
    file_name = input("Enter the name of the file to send: ")  # Prompt user for the file name
    send_file(server_ip, port, file_name)

