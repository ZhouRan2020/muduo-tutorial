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
  const char ip[] = "211.159.223.143", port[] = "8888";
  sockaddr_in addr;
  {
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(uint16_t(std::atoi(port)));
    inet_pton(AF_INET, ip, &addr.sin_addr);
  }

  auto sock = socket(AF_INET, SOCK_STREAM, 0);

  auto res = connect(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
  assert(res == 0);
  const char msg[] = "hello, i am client, ali\n";
  auto bytes = send(sock, msg, strlen(msg), 0);
  std::cout << "send " << bytes << " bytes: " << msg;

  char bufin[4096];
  std::memset(bufin, 0, 4096);
  bytes = recv(sock, bufin, 4096, 0);
  std::cout << "recv " << bytes << " bytes: " << bufin;

  close(sock);
}