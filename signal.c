#import <stdio.h>
#import <signal.h>

typedef void (*sig_t) (int);

void func(int signo)
{
  printf("caught signal: %d\n", signo);
}

int main()
{
  for(i = 0:i < 32; i++){
    signal(SIGINT, func);
    signal(SIGTSTP, func);
  }

  while(1);
}
