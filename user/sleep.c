#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
    fprintf(2, "sleep: params length %d  \n", argc);
    fprintf(2, "sleep: params0 %s  \n", argv[0]);
    fprintf(2, "sleep: params1 %s  \n", argv[1]);

  if(argc < 2){
    fprintf(2, "error: missing parameter sleep time\n");
    exit(1);
  } 
    int slpTime = atoi(argv[1]);
    	sleep(slpTime);
    fprintf(2, "sleep success!  \n");
  
  exit(0);
}
