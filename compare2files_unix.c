/* Mini file compare by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 *
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int compare2files(const char *sname, const char *dname)
{
  int s = open(sname, O_RDONLY);
  if (s == -1)
    return 1; // 1 source not found or can't read
  int d = open(dname, O_RDONLY);
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
      close(s);
      close(d);
      return 3;
    }
    lseek(s, 0, SEEK_SET);
    lseek(d, 0, SEEK_SET);
    for (size_t i = ssize; i != 0; i--)
    {
      read(s, &sa, 1);
      read(d, &db, 1);
      if (sa != db)
        return 4;
    }
    close(s);
    close(d);
    return 0;
  }
}
int main(int argc, char *argv[])
{
  if (argc != 3)
    return -3;
  return compare2files(argv[1], argv[2]);
}
