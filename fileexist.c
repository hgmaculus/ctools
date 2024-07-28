/* Fileexist by H. Gabriel Maculus <gabrielmaculus@gmail.com>
   
 */
#include <stdio.h>
#include <stdbool.h>

//#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// return false if file not exist, or true if file exists and have read permission
bool fileexist(const char *filename)
{
    FILE *f = fopen(filename, "r");
    bool r = f ? true : false;
    if(f) fclose(f);
    return r;
}

int main(int argc, char *argv[])
{
  if(argc == 2 && fileexist(argv[1])) {
    printf("File: %s exist", argv[1]);
  } else {
    printf("File not exist\n");
  }
  return 0;
}
