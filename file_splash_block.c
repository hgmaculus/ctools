/* File splash by H. Gabriel Máculus <gabrielmaculus@gmail.com>
*/

#include <stdio.h>
int main(int argc, char *argv[])
{
  if(argc!=2) {
    puts("Usage: file_splash_block myfile.txt");
    return 0;
  }
  FILE *fp = fopen(argv[1], "r+");
  if(!fp) return 1;
  fseek(fp, 0, SEEK_END);
  size_t sz = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  size_t data_size=1024*1024;
  char data[data_size];
  for(size_t i=data_size; i!=0; i--){
    data[i]='?';
  }
  while(sz > data_size) {
    fwrite(data, data_size, 1, fp);
    sz-=data_size;
  }
  fwrite(data, sz, 1, fp); //remaining

  fclose(fp);
  return 0;
}
