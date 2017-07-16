#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



int main(){
  char buf[512];
  char *fp;
  int  fid[3];
  int  pid;
  int nbyte = 512;
  if (pipe(fid) == -1) {
    fprintf(stderr, "Can't create pipe\n");
    exit(1);
  }
  printf("fid[0]=%d, fid[1]=%d, fid[2]=%d\n", fid[0], fid[1] , fid[2]);
  if ((pid = fork()) == 0) {
    char buf[255];
    int  len;
    close(fid[1]);
    read(fid[0], buf, 255);
    printf("%s", buf);
    close(fid[0]);
  }
  else {
    int les = 0;
    int num;
    scanf("%d",&num);
    for(int i = 1; i <= num*10; i++) {
      les = les + i *num;
    }
    sprintf(buf, "%d", les);
    close(fid[0]);
    write(fid[1], buf, sizeof(buf));
    close(fid[1]);
  }
}
