/* File splash by H. Gabriel Máculus <gabrielmaculus@gmail.com>
*/

#include <stdio.h>
int main(int argc, char *argv[])
{
  if(argc!=2) {
    puts("Usage: file_splash myfile.txt");
    return 0;
  }
  FILE *fp = fopen(argv[1], "r+");
  if(!fp) return 1;
  fseek(fp, 0, SEEK_END);
  size_t sz = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  for(size_t t=sz; t!=0; t--) {
    fputc(63, fp);
    putchar('.');
  }
  fclose(fp);
  return 0;
}
