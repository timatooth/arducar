#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "arduino-serial-lib.h"

int main(int argc, char **argv) {
  char *arduinoPort;
  int serialFD;
  /* Net stuff */
  int sockfd, newsockfd;
  int port = 9090;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int iSetOption = 1;

  if(argc > 1){
    arduinoPort = argv[1];
  } else {
    arduinoPort = "/dev/ttyUSB0";
  }

  /* init arduino serial */
  fprintf(stderr, "Opening Arduino port: %s\n", arduinoPort);
  serialFD = serialport_init(arduinoPort, 9600);
  
  /* init net */
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){ 
    fprintf(stderr, "ERROR on binding port %d\n", port);
    exit(1);
  }
  setsockopt(sockfd,
	     SOL_SOCKET,
	     SO_REUSEADDR,
	     (char*)&iSetOption,
	     sizeof(iSetOption));
  /* wait for connection (this blocks) */
  fprintf(stderr, "Listening on port %d\n", port);
  while(1){
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    fprintf(stderr, "New connection\n");
    if (newsockfd < 0){
      fprintf(stderr, "ERROR on accept connection\n");
    }

    memset(buffer, 0, 256);
    while(read(newsockfd, buffer, 256) > 0){
      serialport_writebyte(serialFD, buffer[0]);
      fprintf(stderr, "Writing byte: %c\n", buffer[0]);
      if(buffer[0] == 'X'){
	fprintf(stderr, "Client sent shutdown instruction\n");
	goto END;
      }
    }
    /*
      printf("Here is the message: %s\n",buffer);
      n = write(newsockfd,"I got your message",18);
      if (n < 0){
      fprintf(stderr, "ERROR writing to socket\n");
      }
    */
  }
 END:
  close(newsockfd);
  close(sockfd);
  serialport_close(serialFD);
  
  return EXIT_SUCCESS;
}
