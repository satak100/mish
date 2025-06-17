#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int
main(int argc, char *argv[])
{
  if(argc != 2 || strlen(argv[1]) != 1){
    fprintf(2, "usage: target <char>\n");
    exit(1);
  }
  char c = argv[1][0];
  setTargetChar(c);
  printf("Target character set to '%c'\n", c);
  exit(0);
}
