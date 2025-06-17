#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: freq <string>\n");
    exit(1);
  }
  int count = countTargetFreq(argv[1]);
  printf("Found %d occurrences of target\n", count);
  exit(0);
}
