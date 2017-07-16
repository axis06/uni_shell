#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include<unistd.h>    //write

int dowork(int new_s);

int main(int argc , char *argv[])
{
    struct addrinfo hints, *res, *res0;
    socklen_t ss_len = sizeof(res);
    int err;
    int s[256];
    int ss;
    int ns;
    int i;
    int new_s;
    int status;


    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family   = AF_INET;

    err = getaddrinfo(NULL, "12345", &hints, &res0);

    if(err){
      exit(0);
    }

    ns = 0;
    for (res = res0; res; res = res->ai_next){
      s[ns] = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
      if(s[ns] < 0){
        perror("socket");
        continue;
      }

      fprintf(stderr, "Create socket: %d",res->ai_family);
      if (bind(s[ns], res->ai_addr, res->ai_addrlen) < 0) {
        perror("bind");
        exit(-1);
      }
      listen(s[ns],5);
      ns ++;
    }
    freeaddrinfo(res0);

    for(i = 0;i < ns; i++){
      if(fork()==0){
          new_s = accept(s[i],(struct sockaddr *)&ss ,&ss_len);
          dowork(new_s);
      }
    }

    wait(&status);
}

int dowork(int new_s){
  char buf[512];
  int cc;
  while(1){
    cc = read(new_s, buf, sizeof(buf));
    write(1,buf,cc);
    write(new_s, buf, cc);
  }

}
