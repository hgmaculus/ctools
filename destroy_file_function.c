/* 13/09/2025 programmers day
   destroy file by H. Gabriel Maculus <gabrielmaculus@gmail.com> */
#include <stdio.h>
#include <stdlib.h>

int file_insert_string(const char *filename, const off_t offset, const char *string) {
  FILE *fp = fopen(filename, "r+");
  if(!fp) return -1;
  fseek(fp, 0, SEEK_END);
  size_t s=ftell(fp); // file size
  if(s < offset) fclose(fp);
  fseek(fp, offset, SEEK_SET); // printf("Seeking file to: %ld\n", ftell(fp));
  fputs(string, fp);
  fclose(fp);
  return 0;
}


int main(int argc, char *argv[]) {
	file_insert_string(argv[1], atol(argv[2]), argv[3]);
   return 0; 
}
