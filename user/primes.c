#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"


void primes(int fds[]){
  int p;
  close(fds[1]);
  if(read(fds[0], &p, 4) > 0){
    fprintf(2, "prime %d\n", p);
    int pid;
    int fds2[2];

    if (pipe(fds2) == -1){
      fprintf(2, "create pipe error\n");
      exit(-1);
    }

    if ((pid = fork()) == 0){ //child
      primes(fds2);
    }else{//parent
      close(fds2[0]);
      int pp;
      while(read(fds[0], &pp, 4) > 0){
        if((pp%p) != 0){
          write(fds2[1], &pp, sizeof(pp));
        }
      }
      close(fds[0]);
      close(fds2[1]);
      wait(0);
    }
  }  
}

int
main(int argc, char *argv[]){
    int n = 35;
    int fds[2];
    int pid;

    if (pipe(fds) == -1){
      fprintf(2, "create pipe error\n");
      exit(-1);
    }

    if((pid=fork()) == 0){//child
      primes(fds);
    }else{
      close(fds[0]);
      fprintf(2, "prime 2\n");
      for (int i = 3; i < n; i++){
        if((i%2) != 0){
            write(fds[1], &i, sizeof(i));
        }
      }
      close(fds[1]);
      wait(0);
    }

    exit(0);
}
