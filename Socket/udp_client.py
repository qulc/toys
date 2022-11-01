import sys
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

data = sys.argv[1].encode()
sock.sendto(data, ('localhost', 5000))

print(sock.recv(1024))
