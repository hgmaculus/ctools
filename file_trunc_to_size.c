#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

// return false if file not exist, or true if file exists
bool fileexist_unix(const char *filename) {
  int f = open(filename, O_RDONLY);
  if(f != -1) {
    close(f);
    return true;
  } else {
    return false;
  }
}

int file_trunc_to_size(const char *filename, size_t s) {
  if(fileexist_unix(filename)) {
    truncate(filename, s);
    return 0;
  } else {
    return 1;
  }
}
int main(int argc, char *argv[])
{
  if(argc != 3) {
    puts("Usage: file_trunc_to_size filename new_size");
    return 1;
  }
  return file_trunc_to_size(argv[1], atol(argv[2]));
}
