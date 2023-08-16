import socket,time

serversocket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
serversocket.bind(('',8888))
serversocket.listen(5)

while True:
    (clientsocket,address)=serversocket.accept()
    data=clientsocket.recv(4096)
    datetime=bytes(time.asctime()+'\n',"utf-8")
    clientsocket.send(data)
    clientsocket.send(datetime)
    clientsocket.close()


