/**@file c4_9chmod.c
 * @brief chmod(2)
 */
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  struct stat statbuf;
  /* turn on ste-group-ID and turn off group-execute*/
  if(stat("foo", &statbuf) < 0){printf("stat error for foo\n"); exit(-1);}
  if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0){printf("chmod error for foo\n"); exit(-1);}
  /* set absolute mode to "rw-r--r--"*/
  if(chmod("bar", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0){printf("chmod error for bar");}
  exit(0);
}
