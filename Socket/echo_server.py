import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('127.0.0.1', 5000))
s.listen(1)

while True:
    conn, addr = s.accept()
    with conn:
        data = conn.recv(1024)
        print(data)
        conn.send(data)

s.close()
