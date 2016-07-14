#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void set_fl(int fd, int flags){
  // flags are file status flags to turn on
  int val;
  if(0 < (val = fcntl(fd, F_GETFL, 0))){
    val |= flags; // turn on flags
    // val |= ~flags; // turn off glags
    if(-1 == fcntl(fd, F_SETFL, val))printf("set fd status flags fail\n");
  }
}
int main(int argc, char* argv[]){
  
  exit(0);
}
