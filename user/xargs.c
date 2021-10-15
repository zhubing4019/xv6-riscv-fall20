#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

void
fork_c(char *argv[]){
    int pid;
    if((pid=fork())< 0){
        fprintf(2, "fork fail.\n", getpid());
        exit(-1);
    }

    if(pid == 0){
        exec(argv[0], argv);
        exit(0);
    }else{
        wait(0);
    }
}


int
main(int argc, char *argv[]){
   for (int i = 0; i < argc; i++){
        // fprintf(2, "param%d: %s\n", i,argv[i]);
    }
    int w_idx = 0;
    char c;
    char buff[512];
    char *_argv[MAXARG];
    for (int i = 1; i < argc; i++){
        _argv[i - 1] = argv[i];
    }

    while(read(0, &c, 1) != 0){
            if(c == '\n'){
                _argv[argc - 1] = buff;
                // fprintf(2, "===read param0: %s\n", _argv[0]);
                // fprintf(2, "===read param1: %s\n", _argv[1]);
                // fprintf(2, "===read param2: %s\n", _argv[2]);
                fork_c(_argv);
                w_idx = 0;
                memset(buff,'\0', sizeof(buff));
            }else{
                // fprintf(2, "===read buff: %s\n", buff);
                memmove(buff + w_idx, &c, 1);
                // fprintf(2, "===read buff: %s\n", buff);
                w_idx++;
            }
        }


  exit(0);
}
