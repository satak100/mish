#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: freq string\n");
    exit(1);
  }
  int count = countTargetFreq(argv[1]);
  if(count < 0){
    fprintf(2, "frequency count failed\n");
    exit(1);
  }
  printf("Found %d occurrences of target\n", count);
  exit(0);
}

