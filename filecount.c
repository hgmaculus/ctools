/* filecount by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 Print number of bytes in file specified by argument	
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *f = fopen(argv[1], "r");
  if(!f) return -1;
  size_t count=0;
  while(!feof(f)) {
    fgetc(f);
    count++;
  }
  printf("Count: %lu\n", count);
  fclose(f);
  return 0;
}
