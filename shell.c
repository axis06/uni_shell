#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
  char buf[512];
  int nbyte = 512;
  int status;
  char *fp;
  char *cp;
  char path[512];
  pid_t pid;

  while(1){
     printf("%% ");

    if((fp = fgets(buf, nbyte, stdin)) == NULL){
       fprintf(stderr,"exiting .....\n");
       exit(1);
    }

    if (*fp == '\n') continue;

     pid = fork();
     if(pid == 0){
       fprintf(stderr,"I would l like to execute %s\n", buf);
       strcpy(path, "/bin/");
       strcat(path, buf);
       cp = index(path, '\n');
       *cp = '\0';
       printf("%s",path);
       execl(path, buf, 0);
       exit(1);
     }else{
       wait(&status);
     }
  }
}
