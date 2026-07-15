/* file descriptor from stdio FILE * by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 Print number of bytes in file specified by argument	
*/
#include <stdio.h>
#include <sys/mman.h>


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


int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1], "r");
  int fd = fileno(fp);
  if (fd == -1) {
    perror("fileno");
    return 1;
  } 
  void *addr = mmap(NULL, filesize(argv[1]), PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    return 1;
  } 
  for(int i = 0; i < 5; i++) {
    printf("%c", ((char *)addr)[i]);
  }
  //printf("FD %d\n", fd);
  munmap(addr, filesize(argv[1]));

  fclose(fp);
  return 0; 
}
