#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void pr_exit(int status){
  if(WIFEXITED(status)){
    printf("normal termination, exit status = %d\n",
	   WEXITSTATUS(status));
  }else if(WIFSIGNALED(status)){
    printf("abnormal termination, signal number = %d%s\n",
	   WTERMSIG(status),
#ifdef WCOREDUMP
	   WCOREDUMP(status) ? "(core file generated":"");
#else
    "");
#endif
  }else if(WIFSTIPPED(status)){
  printf("chiled stopped, signal number = %d\", WSTOPSIG(status));
  }else{
   printf("nothing to dump");
  }
}

int main(void){
pid_t pid;
int status;

if((pid = fork())<0){}else if(pid == 0£©exit(7);
wait(&status);
pr_exit(status);

if((pid = fork())<0){}else if(pid == 0£©abort();
wait(&status);
pr_exit(status);

if((pid = fork())<0){}else if(pid == 0£©status /= 0;
wait(&status);
pr_exit(status);

}
/*
$ ./a.out
normal termination, exit status = 7
abnoremal termination, signal number = 6 (core file generated)
abnoremal termination, signal number = 8 (core file generated)
*/
