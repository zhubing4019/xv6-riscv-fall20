#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
is_dirOrFile(char *path){
  int flag = -1;
  int fd;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return flag;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return flag;
  }

  switch(st.type){
  case T_FILE:
    flag = 1;
    break;

  case T_DIR:
    flag = 0;
    break;
  }
  close(fd);
  return flag;
}

void
find(char *path, char *f_cont)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0)
  {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    fprintf(2, "find error: path must be a directory\n");
    close(fd);
    exit(1);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      {
        continue;
      }
      if(is_dirOrFile(buf)==0){ //dir
        find(buf ,f_cont);
      }else{
        if (strcmp(de.name, f_cont) == 0)
        {
          printf("%s\n", buf);
        }
      }         
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc < 2){
    fprintf(2, "find error: missing parameter\n");
    exit(1);
  } 

  find(argv[1], argv[2]);

  exit(0);
}
