/**@file c3_lseek.c
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void){
  if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1){
    printf("STDIN_FILENO can not seek; errno:%d strerror:%s\n",errno, strerror(errno));
  }else{
    printf("STDIN_FILENO seek ok\n");
  }
  exit(0);
}

