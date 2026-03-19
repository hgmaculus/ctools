/* getfreemem_sysinfo by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
*/
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  struct sysinfo s;

  sysinfo(&s);

  printf("Total: %lu\n", s.totalram);
  printf("Free: %lu\n", s.freeram);
  printf("Buffered: %lu\n", s.bufferram);
  printf("High: %lu\n", s.freehigh);
  printf("Shared: %lu\n", s.sharedram);

  return 0;
}
