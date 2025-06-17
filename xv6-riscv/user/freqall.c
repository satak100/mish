#include "kernel/types.h"
#include "kernel/freq.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf("usage: freqall string\n");
    exit(1);
  }

  struct freq_array arr;
  if(countFreq(argv[1], &arr) < 0){
    printf("countFreq syscall failed\n");
    exit(1);
  }
  int first = 1;
  for(int i = 0; i < 128; i++){
    if(arr.counts[i] > 0){
      if(first){
        printf("%c: %d (user space)\n", (char)i, arr.counts[i]);
        first = 0;
      } else {
        printf("%c: %d\n", (char)i, arr.counts[i]);
      }
    }
  }
  exit(0);
}
