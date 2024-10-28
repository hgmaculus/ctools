#include <stdio.h>
#include <stdbool.h>
// return false if file not exist, or true if file exists
bool fileexist(const char *filename) {
  FILE *f = fopen(filename, "r");
  if(f) {
    fclose(f);
    return true;
  } else {
    return false;
  }
}

size_t filesize(const char *filename) {
  size_t fsize=0;
  FILE *f = fopen(filename, "r");
  fseek(f, 0, SEEK_END);
  fsize = ftell(f);
  fclose(f);
  return fsize;
}


int file_copy_continue(const char *source, const char *destination) {
  if (!fileexist(source)) {
    return -1;
  }

  FILE *fd, *fs;
  
  if(fileexist(destination)) { // continue previous copy
    if(filesize(source) == filesize(destination)) {
     return 0; // files are equal 
    }
    fd = fopen(destination, "a");
  } else {
    fd = fopen(destination, "w"); //new file and new copy
  }
  fs = fopen(source, "r");
  long position=ftell(fd);
  fseek(fs, position, SEEK_SET);
  int c;
  while (!feof(fs)) {
    c = fgetc(fs);
    if(c != EOF) fputc(c, fd);
  }

  fclose(fs);
  fclose(fd);
  return 0;
}


int main(int argc, char *argv[])
{
  return file_copy_continue(argv[1], argv[2]);
}

// finished, all test are passed.
