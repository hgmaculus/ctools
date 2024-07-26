/* Mini Copy by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
*/
#include <stdio.h>

int main(int argc, char *argv[])
{
  if(argc != 3) return -3;
  
  FILE *s = fopen(argv[1], "r");
  FILE *d = fopen(argv[2], "w");
  
  if(!s) {
    fclose(d);
    return -1; // -1 source not found or can't read
  }
  if(!d){
        fclose(s);
	return -2; // -2 destination not write permission or can't write
  } 

  {
    int c;
    while(!feof(s)) {
      c = fgetc(s);
      if(c != EOF) fputc(c, d);
    }
  }

  fclose(s);
  fclose(d);
  return 0;
}
