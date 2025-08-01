#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

size_t filesize(const char *filename) {
  size_t fsize=0;
  int f = open(filename, O_RDONLY);
  fsize = lseek(f, 0, SEEK_END);
  close(f);
  return fsize;
}
int main(int argc, char const *argv[])
{
    printf("File: %s : %ld\n", argv[1], filesize(argv[1]));
    return 0;
}
