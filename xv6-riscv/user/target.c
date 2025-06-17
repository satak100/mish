#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: target char\n");
    exit(1);
  }
  char c = argv[1][0];
  if(setTargetChar(c) < 0){
    fprintf(2, "failed to set target\n");
    exit(1);
  }
  printf("Target character set to '%c'\n", c);
  exit(0);
}

