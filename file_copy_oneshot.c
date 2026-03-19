/* file_copy_oneshot by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
 */
#include <stdio.h>

#include <stdlib.h>

size_t file_size(const char *filename) {
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

/*
  file_copy_oneshot do the entire file copy
  with one read and one write
  all file must be fill in memory assigned with malloc
 */
int file_copy_oneshot(const char *sname, const char *dname){
  size_t sname_size = file_size(sname);
  FILE *s = fopen(sname, "r");

  if(!s) {
    return -1; // -1 source not found or can't read
  }

  FILE *d = fopen(dname, "w");

  if(!d){
    fclose(s);
    return -2; // -2 destination not found or can't read
  } 

  char *buffer = malloc(sname_size + 1);
  if(!buffer) {
    fclose(s);
    fclose(d);
    return -3; // malloc failed
  }

  fread(buffer, sname_size, 1, s);
  fwrite(buffer, sname_size, 1, d);

  free(buffer);
  fclose(s);
  fclose(d);
  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 3) {
    puts("Usage: file_copy_oneshot source destination");
    return -3; 
  }
  file_copy_oneshot(argv[1], argv[2]);
  return 0;
}
