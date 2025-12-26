/* file_copy_continue_unix by H. Gabriel Maculus <gabrielmaculus@gmail.com> */

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>

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
size_t filesize_unix(const char *filename) {
  size_t fsize=0;
  int f = open(filename, O_RDONLY);
  fsize = lseek(f, 0, SEEK_END);
  close(f);
  return fsize;
}

int file_copy_continue_unix(const char *source, const char *destination) {
  if (!fileexist_unix(source)) {
    return -1;
  }

  int fd, fs;
  size_t fs_size;
  if(fileexist_unix(destination)) { // continue previous copy
    if(filesize_unix(source) == filesize_unix(destination)) {
      //puts("Do Nothing");
      return 0; // files are equal, do nothing
    }
    fd = open(destination, O_RDWR);
    printf("Continue Copy at: ");
    fs = open(source, O_RDONLY);
    off_t position=lseek(fd, -1, SEEK_END);
    printf("Position %lu\n", position);
    off_t position_src =  lseek(fs, position, SEEK_SET);
    //printf("Position Source %lu\n", position_src);
    fs_size = filesize_unix(source) - position;
  } else {
    puts("New Copy");
    fs = open(source, O_RDONLY);
    struct stat fs_stat;
    fstat(fs, &fs_stat);
    fd = open(destination, O_RDWR | O_CREAT | O_TRUNC, fs_stat.st_mode); //new file and new copy
    off_t position=lseek(fd, 0, SEEK_END);
    printf("Position Destination %lu\n", position);
    off_t position_src =  lseek(fs, position, SEEK_SET);
    printf("Position Source %lu\n", position_src);
    fs_size = filesize_unix(source) - position;
  }
  {
    char c;
    for(size_t i = fs_size; i!=0; i--) {
      read(fs, &c, 1);
      write(fd, &c, 1);
    }
  }
  close(fs);
  close(fd);
  return 0;
}


int main(int argc, char *argv[])
{
  return file_copy_continue_unix(argv[1], argv[2]);
}

