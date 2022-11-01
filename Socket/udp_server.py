from socketserver import BaseRequestHandler, UDPServer

class UDPHandler(BaseRequestHandler):
    def handle(self):
        data, socket = self.request
        print(data)
        socket.sendto(data.upper(), self.client_address)


with UDPServer(("localhost", 5000), UDPHandler) as server:
    server.serve_forever()
