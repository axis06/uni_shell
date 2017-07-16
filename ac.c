#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void f1(void);
void f2(void);

int counter = 0;


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
        pthread_t thread1, thread2;
        int ret1,ret2;

        ret1 = pthread_create(&thread1,NULL,(void *)f1,NULL);
        ret2 = pthread_create(&thread2,NULL,(void *)f2,NULL);

        void *status1, *status2;
        ret1 = pthread_join(thread1,&status1);
        ret2 = pthread_join(thread2,&status2);



        printf("done\n");
        printf("%d\n", counter);
        return 0;
}


void f1(void)
{
  size_t i;
  for(i=0; i<50000; i++){
    int r;
    r = pthread_mutex_lock(&m);
    if (r!=0){
      errc(EXIT_FAILURE,r,"not lock");
    }

    counter ++;

    r = pthread_mutex_unlock(&m);
    if (r!=0){
      errc(EXIT_FAILURE,r,"not lock");
    }
  }
}

void f2(void)
{
  size_t i;
  for(i=0; i<50000; i++){
    int r;
    r = pthread_mutex_lock(&m);
    if (r!=0){
      errc(EXIT_FAILURE,r,"not lock");
    }

    counter ++;

    r = pthread_mutex_unlock(&m);
    if (r!=0){
      errc(EXIT_FAILURE,r,"not lock");
    }
  }
}
