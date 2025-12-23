#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  if(argc != 3) return -1;
  int src = open(argv[1], O_RDONLY);
  off_t total = lseek(src, 0, SEEK_END);
  struct stat src_stat;
  fstat(src, &src_stat);
  close(src);
  int dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, src_stat.st_mode);
  // grant size in destination file for source file
  int ret = fallocate(dst, 0, 0, total);
  if(!ret) puts("Allocation succeed");
  close(dst);
  return 0;
}
