#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "arduino-serial-lib.h"

int main(void) {
int serialFD;

/* Net stuff */
int sockfd, newsockfd;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
int iSetOption = 1;

/* init arduino serial */
 serialFD = serialport_init("/dev/ttyUSB0", 9600);
  
 /* init net */
 sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

 memset(&serv_addr, 0, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(9090);
 if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){ 
   fprintf(stderr, "ERROR on binding port 9090");
 }
 setsockopt(sockfd,
	    SOL_SOCKET,
	    SO_REUSEADDR,
	    (char*)&iSetOption,
	    sizeof(iSetOption));
 /* wait for connection (this blocks) */
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
     fprintf(stderr, "Writing byte\n");
     if(buffer[0] == 'X'){
       fprintf(stderr, "Client sent shutdown instruction\n");
       goto END;
     }
   }

   printf("Here is the message: %s\n",buffer);
   n = write(newsockfd,"I got your message",18);
   if (n < 0){
     fprintf(stderr, "ERROR writing to socket");
   }
 }
 END:
 close(newsockfd);
 close(sockfd);
 serialport_close(serialFD);
  
 return EXIT_SUCCESS;
}
