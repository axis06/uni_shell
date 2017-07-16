#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/param.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 512

int main(int argc, char **argv) {

  char send_buf[BUF_SIZE];
  char host[BUF_SIZE] = "";
  unsigned short port = 12345;


  int s;
  int err;
  char *servhost;
  struct sockaddr_in server;
  struct servent *service;

  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof(hints));//0で埋める
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family   = AF_INET;


  servhost = argv[1];



  if ((err = getaddrinfo(servhost, "12345", &hints, &res)) != 0) {
      printf("error %d\n", err);
      return 1;
  }

  if ((s = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
      fprintf(stderr, "error socket\n");
      return 1;
  }
  if (connect(s, res->ai_addr, res->ai_addrlen) != 0) {
    fprintf(stderr, "error connect\n");
    return 1;
  }

  printf("Connected to http://%s:%hu \n", servhost, port);


  int nbyte = 512;
  char *fp;

  //sprintf(send_buf, "GET /");
  //write(s, send_buf, strlen(send_buf));

  while(1) {

    if((fp = fgets(send_buf, nbyte, stdin)) == NULL){
      return 0;
    }else{
      write(s, send_buf, strlen(send_buf));
    }


    while(1) {
        char buf[BUF_SIZE];
        int read_size;
        read_size = read(s, buf, BUF_SIZE);

        if (read_size > 0) {
          write(1, buf, read_size);
        }
        else {
            break;
        }
    }
  }

   close(s);
   return 0;
}
