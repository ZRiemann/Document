#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
int fd;
do{
if((fd = open("file.hole", O_CREAT | O_RDWR | O_TRUNC))<0)break;
if(write(fd, buf1, 10)!= 10){printf("write error.\n");break;}
if(lseek(fd, 1024, SEEK_SET) == -1){printf("seek to 1024 fail.\n");break;}
if(write(fd, buf2, 10) != 10){printf("write buf2 error.\n");}
}while(0);
exit(0);
}
