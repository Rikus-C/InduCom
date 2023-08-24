import os
import socket

os.system("clear");

def main():
    host = '127.0.0.1'  # Use '0.0.0.0' to listen on all available interfaces
    port = 12345       # Choose an available port number
    
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)  # Number of queued connections
    
    print(f"Server listening on {host}:{port}")
    
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection established with {client_address}")
        
        try:
            while True:
                data = client_socket.recv(1024)  # Receive data from the client
                if not data:
                    break
                message = data.decode('utf-8')
                print(f"Received: {message}")
                
                response = f"Server received: {message}"
                client_socket.send(response.encode('utf-8'))  # Send response to client
        except Exception as e:
            print(f"Error: {e}")
        finally:
            client_socket.close()
            print(f"Connection with {client_address} closed")

if __name__ == "__main__":
    main()
