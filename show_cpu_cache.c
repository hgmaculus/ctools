/*
  show cache L1, L2 and L3 size and alignment
  H. Gabriel Maculus (gabrielmaculus@gmail.com)
*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  
  printf("Cache L1 line (Data): %ld\n", sysconf(_SC_LEVEL1_DCACHE_LINESIZE));
  printf("Cache L1 line (Instruction): %ld\n", sysconf(_SC_LEVEL1_ICACHE_LINESIZE));
  printf("Cache L1 DSize: %ld\n", sysconf(_SC_LEVEL1_DCACHE_SIZE));
  printf("Cache L1 ISize: %ld\n", sysconf(_SC_LEVEL1_ICACHE_SIZE));

  printf("Cache L2 line: %ld\n", sysconf(_SC_LEVEL2_CACHE_LINESIZE));
  printf("Cache L2 Size: %ld\n", sysconf(_SC_LEVEL2_CACHE_SIZE));

  printf("Cache L3 Size: %ld\n", sysconf(_SC_LEVEL3_CACHE_SIZE));
  printf("Cache L3 Line: %ld\n", sysconf(_SC_LEVEL3_CACHE_LINESIZE));

  return 0;
}
