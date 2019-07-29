import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.connect(('127.0.0.1', 5000))
	s.sendall(b'Hello World!')

	data = s.recv(512)

print(data)
