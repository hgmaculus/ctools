/*
   Static Chrono by H. Gabriel Maculus <gabrielmaculus@gmail.com>
   one call for init, second call for finish
 */
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void chrono() {
  static clock_t start, stop;
  static int started = 0;
  if(started) {
    stop = clock();
    printf("Timing %f\n", (double)(stop - start)/CLOCKS_PER_SEC);
    started = 0;
  } else {
    start = clock();
    started = 1;
  }
}
int main(int argc, char *argv[])
{
  chrono();
  puts("");
  chrono();

  chrono();
  printf("\n");
  chrono();

  return 0;
}
