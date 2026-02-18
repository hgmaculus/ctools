/*
  destroy_file_unix by H. Gabriel Maculus <gabrielmaculus@gmail.com>
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  puts("Usage: ./destroy_file file_to_destroy whence text-to-insert ");
  if(argc != 4) return 1;
  int fp = open(argv[1], O_RDWR);
  if(fp == -1) return -1;
  size_t s=lseek(fp, 0, SEEK_END); // file size
  size_t parm2 = atol(argv[2]);
  printf("File size to: %ld\n", s);
  if(s < parm2) {
    close(fp);
    return 2; 
  }
  printf("Writing %s into %lu position\n", argv[3], lseek(fp, parm2, SEEK_SET));
  write(fp, argv[3], strlen(argv[3]));
  close(fp);
  return 0;
}
