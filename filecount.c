/* filecount by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 Print number of bytes in file specified by argument	
*/
#include <stdio.h>

size_t file_count(const char *restrict filename) {
  FILE *f = fopen(filename, "r");
  if(!f) return -1;
  size_t count=0;
  while(!feof(f)) {
    fgetc(f);
    count++;
  }
  fclose(f);
  return count;
}
int main(int argc, char *argv[])
{
  printf("Count %zu\n", file_count(argv[1]));
  return 0; 
}
