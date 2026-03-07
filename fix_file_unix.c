/* Mini fix file by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

bool fileexist_unix(const char *filename)
{
  int f = open(filename, O_RDONLY);
  if (f != -1)
  {
    close(f);
    return true;
  }
  else
  {
    return false;
  }
}

size_t filesize_unix(const char *filename)
{
  size_t fsize = 0;
  int f = open(filename, O_RDONLY);
  fsize = lseek(f, 0, SEEK_END);
  close(f);
  return fsize;
}

int file_copy_continue_unix(const char *source, const char *destination)
{
  if (!fileexist_unix(source))
  {
    return -1;
  }

  int fd, fs;
  size_t fs_size;
  if (fileexist_unix(destination))
  { // continue previous copy
    if (filesize_unix(source) == filesize_unix(destination))
    {
      // puts("Do Nothing");
      return 0; // files are equal, do nothing
    }
    fd = open(destination, O_RDWR);
    printf("Continue Copy at: ");
    fs = open(source, O_RDONLY);
    off_t position = lseek(fd, -1, SEEK_END);
    printf("Position %lu\n", position);
    off_t position_src = lseek(fs, position, SEEK_SET);
    // printf("Position Source %lu\n", position_src);
    fs_size = filesize_unix(source) - position;
  }
  else
  {
    fs = open(source, O_RDONLY);
    struct stat fs_stat;
    fstat(fs, &fs_stat);
    fd = open(destination, O_RDWR | O_CREAT | O_TRUNC, fs_stat.st_mode); // new file and new copy
    off_t position = lseek(fd, 0, SEEK_END);
    printf("Position Destination %lu\n", position);
    off_t position_src = lseek(fs, position, SEEK_SET);
    printf("Position Source %lu\n", position_src);
    fs_size = filesize_unix(source) - position;
  }
  {
    char c;
    for (size_t i = fs_size; i != 0; i--)
    {
      read(fs, &c, 1);
      write(fd, &c, 1);
    }
  }
  close(fs);
  close(fd);
  return 0;
}

int fix_file_unix(const char *sname, const char *dname)
{
  int s = open(sname, O_RDONLY);
  if (s == -1)
    return 1; // 1 source not found or can't read
  int d = open(dname, O_RDWR);
  if (d == -1)
  {
    close(s);
    return 2; // 2 destination not found or can't read
  }
  {
    char sa, db;
    size_t ssize = lseek(s, 0, SEEK_END); // file size source
    size_t dsize = lseek(d, 0, SEEK_END); // file size destination
    if (ssize != dsize)
    { // files of different size
      ftruncate(d, ssize);
    }
    lseek(s, 0, SEEK_SET);
    lseek(d, 0, SEEK_SET);
    printf("%s size: %zu\n", sname, ssize);
    printf("%s size: %zu\n", dname, dsize);
    for (size_t i = ssize; i != 0; i--)
    {
      read(s, &sa, 1);
      read(d, &db, 1);
      if (sa != db)
      {
        printf("Fix at: %zu\n", lseek(d, -1, SEEK_CUR));
        write(d, &sa, 1);
      }
    }
    close(s);
    close(d);
    return 0;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    puts("Usage: fix_file_unix source_file destination_file");
    return -3;
  }
  size_t s_size = filesize_unix(argv[1]);
  size_t d_size = filesize_unix(argv[2]);

  file_copy_continue_unix(argv[1], argv[2]); // after continue copy do the check
  fix_file_unix(argv[1], argv[2]); // after continue copy do the check

  return 0;
}
