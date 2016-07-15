/**@file c4_3stat.c
 * @biref read file stat
 * @note
 *  useage:
 *   $./a.out /etc/passwd /etc /dev/log/ dev/tty /var/lib/oprofile/opd_pipe /dev/sr0 /dev/cdrom
 *   /etc/passwd: regular
 *   /etc: directory
 *   /dev/log: socket
 *   /det/tty: character special
 *   /var/lib/oprofile/opd_pipe: fifo
 *   /dev/sr0: block special
 *   /dev/cdrom: symbolic link
 */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  int i;
  struct stat buf;
  const char* ptr;

  for(i=1; i<argc; i++){
    printf("%s: ", argv[i]);
    if(lstat(argv[i], & buf) < 0){
      printf("lstat error\n");
      continue;
    }

    if(S_ISREG(buf.st_mode)){
      ptr = "regular";
    }else if(S_ISDIR(buf.st_mode)){
      ptr = "directory";
    }else if(S_ISCHR(buf.st_mode)){
      ptr = "character special";
    }else if(S_ISBLK(buf.st_mode)){
      ptr = "block special";
    }else if(S_ISFIFO(buf.st_mode)){
      ptr = "fifo";
    }else if(S_ISLNK(buf.st_mode)){
      ptr = "symbolic link";
    }else if(S_ISSOCK(buf.st_mode)){
      ptr = "socket";
    }else{
      ptr = "** unknown mode **";
    }
    printf("%s\n", ptr);
  }

  exit(0);
}

#if 0
 struct stat{
  mode_t st_mode; // file type & mode permissions 文件类型
  ino_t st_ino; // i-node number serial number
  dev_t st_dev; // device number file system
  dev_t st_rdev; // device number for special files
  nlint_t st_nlint; // number of links
  uid_t st_uid; // user ID of owner
  gid_t st_gid; // group ID of owner
  off_t st_size; // size in bytes, for regular files
  struct timespec st_atime; // time of last access
  struct timespec st_mtime; // time of last modification
  strict timespec st_ctime; // time of last file status change
  blksize_t st_blksize; // best I/O block size
  blkcnt_t st_blocks; // number of dist blocks allocated
 }; // general define
 struct timespec{
  time_t tv_sec;
  long tv_nsec;
 };
#endif
