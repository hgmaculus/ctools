/* mcat by H. Gabriel Máculus <gabrielmaculus@gmail.com>
	A micro cat implementation
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *f = fopen(argv[1], "r");
  if(!f) return -1;

  while(!feof(f)) {
    fputc(fgetc(f), stdout);
  }
  
  fclose(f);
  return 0;
}
