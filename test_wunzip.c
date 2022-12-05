#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
readingfile(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(2, " write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(2, " read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    readingfile(0);
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(2, " cannot open %s\n", argv[i]);
      exit();
    }
    readingfile(fd);
// it will read file  first in binary format  and then unzip file  using 
// wunzip system call 
  //  wunzip(fd);
close(fd);
  }
exit();
}

// system call returning a number;
int
sys_unzip(void)
{
  int fd;
  struct file *f;
  if(argfd(0, &fd, &f) < 0){
    return -1;
    }
  myproc()->ofile[fd] = 0;
  fileclose(f);
  return 0;  
}

