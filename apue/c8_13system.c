/**@file c8_13system.c
 * @brief a sample implement of system(2)
 * @note
 * version without signal handling
 * -c tell shell get cmdstring not stdin or other
 */
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int system(const char *cmdstring){
  pid_t pid;
  int status;

  if(cmdstring == NULL) return(1);

  if((pid == fork()) < 0){
    status = -1; /* probaly out of processes*/
  }else if(pid == 0){
    /*child*/
    execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
    _exit(127);
  }
  /*parent*/
  while(waitpid(pid, &status, 0)<0){
    if(error != EINTR){
      status = -1; /* error other then EINTR for wait pid() */
      break;
    }
  }
  return(status);
}
