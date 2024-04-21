import socket

def start_client(host, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))
    print(f"Connected to server at {host}:{port}")

    while True:
        message = input("You: ")
        client.send(message.encode())
        data = client.recv(1024).decode()
        print(f"Server: {data}")

if __name__ == "__main__":
    HOST = socket.gethostbyname(socket.gethostname())  # localhost
    PORT = 9999
    start_client(HOST, PORT)

