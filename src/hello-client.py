import os,socket,sys
#import sys

#socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
if __name__ == '__main__':
    sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((sys.argv[1],9000))
    sock.send(bytes(os.getlogin()+ '\n','utf-8'))
    message=sock.recv(4096)
    print(message)
    sock.close()