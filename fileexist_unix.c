#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

bool fileexist(const char *filename) {
  int f = open(filename, O_RDONLY);
  if(f != -1) {
    close(f);
    return true;
  } else {
    return false;
  }
}

int main(int argc, char const *argv[])
{
    if(fileexist(argv[1])) puts("Exist!");
    else puts("Not exist");
    return 0;
}
