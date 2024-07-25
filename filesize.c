/* filesize by H. Gabriel Máculus <gabrielmaculus@gmail.com>
	
*/
#include <stdio.h>
 
int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "r");
  if(!f) return -1;
  
  fseek(f, 0, SEEK_END);
  size_t fssize = ftell(f);
  
  fclose(f);
  
  printf("filesize: %zd\n", fssize);
  
  return 0;
}
