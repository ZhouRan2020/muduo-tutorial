#include <arpa/inet.h>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
//#include <cstrings>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
//#include <cunistd>

int main() {

  const char ip[] = "10.0.4.7", port[] = "8888";
  sockaddr_in serveraddr;
  {
    std::memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(uint16_t(std::atoi(port)));
    inet_pton(AF_INET, ip, &serveraddr.sin_addr);
  }

  auto serversocket = socket(AF_INET, SOCK_STREAM, 0);
  assert(serversocket >= 0);

  auto res = bind(serversocket, reinterpret_cast<sockaddr *>(&serveraddr),
                  sizeof(serveraddr));
  assert(res != -1);

  res = listen(serversocket, 5);
  assert(res != -1);

  while (true) {
    sockaddr_in clientaddr;
    socklen_t clientaddrlen;
    auto clientsocket =
        accept(serversocket, reinterpret_cast<sockaddr *>(&clientaddr),
               &clientaddrlen);

    char bufin[4096];
    std::memset(bufin, 0, 4096);
    auto bytes = recv(clientsocket, bufin, 4096, 0);
    std::cout << "recv " << bytes << " bytes: " << bufin;

    const char msg[] = "hello, i am server, tx\n";
    bytes = send(clientsocket, msg, strlen(msg), 0);
    std::cout << "send " << bytes << " bytes: " << msg;

    close(clientsocket);
  }
  close(serversocket);
}