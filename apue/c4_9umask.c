/**@file c4_9umask.c
 * @brief set umask
 */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main(void){
  umask(0);
  if(creat("foo", RWRWRW) < 0){printf("create error for foo\n");}

  umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  if(creat("bar", RWRWRW) < 0){printf("create error for bar");}

  exit(0);
}
