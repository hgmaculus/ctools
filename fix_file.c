/* Mini fix file compare by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
 */
#include <stdio.h>
#include <stdbool.h>

int file_trunc(const char *a) {
  FILE *f = fopen(a, "w"); // truncate to 0, -> extract to function
  fclose(f);
  return 0;
}
// return false if file not exist, or true if file exists
bool fileexist(const char *filename) {
  FILE *f = fopen(filename, "r");
  if(f) {
    fclose(f);
    return true;
  } else {
    return false;
  }
}

size_t filesize(const char *filename) {
  size_t fsize=0;
  FILE *f = fopen(filename, "r");
  if(!f) {
    fprintf(stderr, "filesize(): file not found %s\n", filename);
    return 0;
  }
  fseek(f, 0, SEEK_END);
  fsize = ftell(f);
  fclose(f);
  return fsize;
}


int file_copy_continue(const char *source, const char *destination) {
  if (!fileexist(source)) {
    return -1;
  }

  FILE *fd, *fs;
  
  if(fileexist(destination)) { // continue previous copy
    if(filesize(source) == filesize(destination)) {
      return 0; // files are equal 
    }
    fd = fopen(destination, "a");
  } else {
    fd = fopen(destination, "w"); //new file and new copy
  }
  fs = fopen(source, "r");
  long position=ftell(fd);
  fseek(fs, position, SEEK_SET);
  int c;
  while (!feof(fs)) {
    c = fgetc(fs);
    if(c != EOF) fputc(c, fd);
  }

  fclose(fs);
  fclose(fd);
  return 0;
}

/*
  only works with file of same size
*/
int fix_file(const char *sname, const char *dname){
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
  if(argc != 3) return -3;
  size_t s_size =filesize(argv[1]);
  size_t d_size =filesize(argv[2]);
  if(s_size > d_size) { // destination maybe incomplete
    file_copy_continue(argv[1], argv[2]);// puts("Destination incomplete: calling file_copy_continue");
    fix_file(argv[1], argv[2]);
  } else if(d_size > s_size) { // need trunc to s_size
    file_trunc(argv[2]);
    file_copy_continue(argv[1], argv[2]);// puts("Destination broken: copy new file");
  } else if(d_size == s_size) {
    fix_file(argv[1], argv[2]);
  }
  
  return 0;
}
