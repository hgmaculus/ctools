/* File splash by H. Gabriel Máculus <gabrielmaculus@gmail.com>
*/
#include <stdio.h>
#include <stdbool.h>

bool file_splash(const char *restrict filename) {
  FILE *fp = fopen(filename, "r+");
  if(!fp) return false;
  fseek(fp, 0, SEEK_END);
  size_t sz = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  for(size_t t=sz; t!=0; t--) {
    fputc(63, fp);
    putchar('.');
  }
  fclose(fp);
  return true;
}
int main(int argc, char *argv[])
{
  if(argc!=2) {
    puts("Usage: file_splash myfile.txt");
    return 0;
  }
  file_splash(argv[1]);

  return 0;
}
