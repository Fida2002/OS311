#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];


void
bylines(int fd)
{
  int n;
  int count_lines=1;
  while((n = read(fd, buf, sizeof(buf))) > 0) {
    printf("%d ",count_lines);
    for (int i=0;i<n;i++)
    {
      printf("%c",buf[i]);
      if(buf[i]=='\n')
      {

        count_lines+=1;

        if(i<n-1)
        printf("%d ",count_lines);


      }
    }
}
}

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {

    if (write(1, buf, n) != n) {
      fprintf(2, "cat: write error\n");
      exit(1);
    }
  }
  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  int check=1;
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit(0);
  }
  if(argc>1)
	{
	if(!strcmp(argv[1], "-n"))
	{
	check++;}
	}

  for(i = check; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    if(check==2)
    {
      bylines(fd);
    }
    else
    {
      cat(fd);
    }
    close(fd);
  }
  exit(0);
}
