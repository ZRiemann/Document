#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE 4096

int main(void){
  int n;
  char buf[BUFFSIZE];

  while(0 < (n = read(STDIN_FILENO, buf, BUFFSIZE))){
    write(STDOUT_FILENO, buf, n);
  }

  exit(0);
}
