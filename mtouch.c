/* mtouch by H. Gabriel Máculus <gabrielmaculus@gmail.com>
  Create a new file like unix touch with zero bytes
*/
#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *fs = fopen(argv[1], "w");
  if(!fs) return -1;
  fclose(fs);
  return 0;
}
