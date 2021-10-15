#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    int pid;
    int result = -1;
    int fd[2];
	int fd0[2];
    char line[1];
	
    //create pipe
    result = pipe(fd);
    if(result == -1){
        fprintf(2, "create pipe fail.\n", getpid());
        exit(-1);
    }
	
	result = pipe(fd0);
    if(result == -1){
        fprintf(2, "create pipe fail.\n", getpid());
        exit(-1);
    }

  //fork
  pid = fork();
  if(result == -1){
        fprintf(2, "fork fail.\n", getpid());
        exit(-1);
  }else if(pid == 0){//child
        close(fd[1]);               
        read(fd[0], line, 1);
       // fprintf(2, "child pid %d: received ping,rev msg: %s, fd_r:%d fd_w:%d \n", getpid(), line, fd[0], fd[1]);
		fprintf(2, "%d: received ping\n", getpid());
		close(fd[0]);              
		
		close(fd0[0]);                
		write(fd0[1], "2", 1);
		close(fd0[1]);              
  }else{//parent
  		close(fd[0]);                
		write(fd[1], "1", 1);
        close(fd[1]);               
		
		close(fd0[1]);                
        read(fd0[0], line, 1);
	//	fprintf(2, "parent pid %d: received pong,rev msg: %s, fd_r:%d fd_w:%d \n", getpid(), line, fd[0], fd[1]);
		fprintf(2, "%d: received pong\n", getpid());
		wait(0);
		close(fd0[0]);  
  }
	exit(0);		
}

