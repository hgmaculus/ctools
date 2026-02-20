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
  if(!f) {
    fprintf(stderr, "filesize(): file not found %s\n", filename);
    return 0;
  }
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
    if(fd == NULL) return 1;
  } else {
    fd = fopen(destination, "w"); //new file and new copy
    if(fd == NULL) return 2;
  }
  fs = fopen(source, "r");
  if(fs == NULL) {
    fclose(fd);
    return 3;
  }
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
