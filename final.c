
//
// Working Shell
// Furuta Katumi


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char**argv) {

  FILE *ff;

  char buf[512];
  int nbyte = 512;
  int status;
  char *fp;
  char *cp;
  char s[256];
  char pathname[256];
  char path[512];
  int l_time;
  pid_t pid;
  time_t s_st,s_se,s_ss;
  clock_t c_s,c_e;

  char name[50][256];
  char url[50][256];


  int i;
  char *argv_c[50];

  char *project;
  project = "Personal";

  if ((ff = fopen("/tmp/.workshell", "a")) == NULL) {
  }else{
    fclose(ff);
  }


  while(1){

    if (strcmp(project, "Personal") != 0){
      s_ss = time(NULL);
      l_time = (int)(s_ss-s_st);
      printf("<%s><%d>%% ",project,l_time);
    }else{
      printf("<%s>%% ",project);
    }

    if((fp = fgets(buf, nbyte, stdin)) == NULL){
       fprintf(stderr,"exiting .....\n");
       exit(0);
    }

    if (*fp == '\n') continue;

    for (i=0;i<49;i++){
      if ((argv_c[i] = strtok(fp," \t\n")) == NULL)
        break;
      fp = NULL;
    }


    if (strcmp(argv_c[0], "wwl") == 0) {
      if ((ff = fopen("/tmp/.workshell", "r")) == NULL) {
        printf("err\n");
      }else{
        while (fgets(s, 256, ff) != NULL) {
          printf("%s", s);
        }
        fclose(ff);
      }
    }

    if (strcmp(argv_c[0], "wws") == 0) {

      if ((ff = fopen("/tmp/.workshell", "r")) == NULL) {
        printf("err\n");
      }else{

        char d[512];
        char *cs;
        char *url;
        int i,n,ret;

        while (fgets(d, 512, ff) != NULL)
        {
            cs = strtok(d, ",");
            printf("%s %s\n", cs, argv_c[1]);
            if(strcmp(cs,argv_c[1]) == 0){
              url = strtok(NULL,",");
              cp = index(url, '\n');
              *cp = '\0';
              chdir(url);
              continue;
            }


        }

        fclose( ff );

      }
      project = argv_c[1];
      s_st = time(NULL);
    }

    if (strcmp(argv_c[0], "wwe") == 0) {
      project = "Personal";
      s_se = time(NULL);
      printf("%d秒でした。\n", (int)(s_se-s_st));
    }

    if (strcmp(argv_c[0], "www") == 0) {

      if(strcmp(argv_c[1], "-s") == 0) {

        memset(pathname, '\0', 256);
        getcwd(pathname, 256);
        printf("%s\n", pathname);

        ff = fopen("/tmp/.workshell", "a");

        fprintf(ff,"%s,%s\n",argv_c[2],pathname);
        fclose(ff);
      }

    }




    if (strcmp(argv_c[0], "exit") == 0) {
      exit(0);
    }

    if(strcmp(argv_c[0], "cd") == 0){
      chdir (argv_c[1]);
    }

    pid = fork();
    if(pid == 0){
      execvp (argv_c[0], argv_c);
      exit(-1);
     }else{
       wait(&status);
     }
  }
}
