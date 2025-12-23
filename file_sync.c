/* file_sync by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
 */
#include <stdio.h>
/*
  only works with files of same size
*/
int file_sync(const char *sname, const char *dname){
  FILE *s = fopen(sname, "r");
  FILE *d = fopen(dname, "r+");

  if(!s) {
    fclose(d);
    return -1; // -1 source not found or can't read
  }
  if(!d){
    fclose(s);
    return -2; // -2 destination not found or can't read
  } 
  {
    char sa, db;
    int ret;
    while(!feof(s)) {
      sa = fgetc(s);
      db = fgetc(d);
      if(sa != db ) { // difference
	printf("Fixing difference at: %ld\n", ftell(s));
	fseek(d, -1, SEEK_CUR);
	ret = fputc(sa, d);
      }
    }
  }
  fclose(s);
  fclose(d);
  return -1;
}

int main(int argc, char *argv[])
{
  if(argc != 3) {
    puts("Usage: filesync source destination");
    return -3; 
  }
  file_sync(argv[1], argv[2]); // file are equal size, check for differences
  return 0;
}
