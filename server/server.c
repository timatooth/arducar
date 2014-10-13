#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "arduino-serial-lib.h"
#define DEBUG_ARDUCAR 0

int main(int argc, char **argv) {
  char *arduinoPort;
  int serialFD;
  /* Net stuff */
  int sockfd, newsockfd;
  int port = 9090;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int iSetOption = 1; /* related to socket binding */
  int bytesRead, i;

  if(argc > 1){
    arduinoPort = argv[1];
  } else {
    arduinoPort = "/dev/ttyUSB0";
  }

  /* init arduino serial */
  fprintf(stderr, "Opening Arduino port: %s\n", arduinoPort);
  serialFD = serialport_init(arduinoPort, 9600);
  if(-1 == serialFD){
    fprintf(stderr, "Error opening Arduino port: %s\n", arduinoPort);
    exit(1);
  }

  /* init net */
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  /* Make the port available once the program exits */
  setsockopt(sockfd,
       SOL_SOCKET,
       SO_REUSEADDR,
       (char*)&iSetOption,
       sizeof(iSetOption));

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
    fprintf(stderr, "ERROR on binding port %d\n", port);
    exit(1);
  }


  /* wait for connection (this blocks) */
  fprintf(stderr, "Listening on port %d\n", port);
  while(1){
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0){
      fprintf(stderr, "ERROR on accepting connection\n");
      continue;
    }

    fprintf(stderr, "Connection: %s", inet_ntoa(cli_addr.sin_addr));
    fprintf(stderr, ": %d\n", (int) ntohs(cli_addr.sin_port));

    memset(buffer, 0, 256);
    while((bytesRead = read(newsockfd, buffer, 256)) > 0){
      for(i = 0; i < bytesRead; i++){
        serialport_writebyte(serialFD, buffer[i]);
        if(DEBUG_ARDUCAR){
          fprintf(stderr, "Writing byte: %#02x\n", buffer[i]);
        }
      }
    }
  }

  close(newsockfd);
  close(sockfd);
  serialport_close(serialFD);

  return EXIT_SUCCESS;
}
