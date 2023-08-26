import os
import socket

os.system("clear")

def main():
    host = '127.0.0.1'
    port = 12345
    
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Use SOCK_DGRAM for UDP
    server_socket.bind((host, port))
    
    print(f"Server listening on {host}:{port}")
    
    while True:
        try:
            data, client_address = server_socket.recvfrom(1024)  # Receive data and client address
            message = data.decode('utf-8')
            print(f"Received from {client_address}: {message}")
            
            response = f"Server received: {message}"
            server_socket.sendto(response.encode('utf-8'), client_address)  # Send response to client
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    main()







