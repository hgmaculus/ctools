/* filesize by H. Gabriel Máculus <gabrielmaculus@gmail.com>
	
*/
#include <stdio.h>
 
size_t filesize(const char *filename) {
  FILE *f = fopen(filename, "r");
  if(!f) {
    fprintf(stderr, "filesize(): file not found %s\n", filename);
    return 0;
  }
  
  fseek(f, 0, SEEK_END);
  size_t fsize = ftell(f);
  fclose(f);
  return fsize;
}

int main(int argc, char *argv[]) {
  
  printf("filesize: %zd\n", filesize(argv[1]));
  
  return 0;
}
