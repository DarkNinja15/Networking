import socket
import threading

def handle_client(client_socket, client_address):
    print(f"Accepted connection from {client_address}")
    while True:
        try:
            data = client_socket.recv(1024).decode()
            if not data:
                break
            print(f"Client ({client_address}): {data}")
            message = input("You: ")
            client_socket.send(message.encode())
        except:
            break
    print(f"Connection from {client_address} closed.")
    client_socket.close()

def start_server(host, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)
    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, client_address = server.accept()
        client_handler = threading.Thread(target=handle_client, args=(client_socket, client_address))
        client_handler.start()

if __name__ == "__main__":
    HOST = socket.gethostbyname(socket.gethostname())  # localhost
    PORT = 9999
    start_server(HOST, PORT)

