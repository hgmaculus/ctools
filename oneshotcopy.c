/* One Shot Copy by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * One Read and One Write
 */
#include <stdio.h>
#include <stdlib.h>

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
  
  // file size start
  FILE *f = fopen(argv[1], "r");
  if(!f) return -1;
  
  fseek(f, 0, SEEK_END);
  size_t fssize = ftell(f);
  
  fclose(f);
  // file size end

  // assign memory start
  void *mem = malloc(fssize);
  if(!mem) return -2; // mem failed
  
  // assign memory end
  
  // block of copy
  size_t nreaded = fread(mem, fssize, 1, s);
  if(nreaded != 1) puts("Read failed!");
  // printf("nreaded=%zu fssize=%zu\n", nreaded, fssize);
  size_t nwritten = fwrite(mem, fssize, 1, d);
  //  printf("nreaded=%zu fssize=%zu\n", nreaded, fssize);
  if(nwritten != 1) puts("Write failed!");
  // block of copy
  
  fclose(s);
  fclose(d);
  free(mem);
  return 0;
}
