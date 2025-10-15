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
    started = 0;
    stop = clock();
    printf("Timing %f\n", (double)(stop - start)/CLOCKS_PER_SEC);
  } else {
    started = 1;
    start = clock();
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
