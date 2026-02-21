/* file_sync by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
 */
#include <stdio.h>
#include <unistd.h>

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

int file_sync(const char *sname, const char *dname){
  { // Truncate destination file to same size of source
    size_t sname_size = filesize(sname);
    if(sname_size != filesize(dname)) {
      truncate(dname, sname_size);
    }
  }
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
    while(!feof(s)) {
      sa = fgetc(s);
      db = fgetc(d);
      if(sa != db ) { // difference
	printf("Fixing difference at: %ld\n", ftell(s));
	fseek(d, -1, SEEK_CUR);
	fputc(sa, d);
      }
    }
  }
  fclose(s);
  fclose(d);
  return 0;
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
