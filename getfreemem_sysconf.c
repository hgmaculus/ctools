/* getfreemem_sysconf by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
*/
#include <unistd.h>
#include <stdio.h>

size_t getfreemem() { return sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE); }

int main(int argc, char *argv[])
{
  printf("Freemem: %lu\n", getfreemem());
  return 0;
}
