/* show_progress_bar_mini by H. Gabriel Máculus <gabrielmaculus@gmail.com>
*/
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
void show_progress_bar_mini(int8_t percent) {
    fputc('\r', stdout);
    fputc('[', stdout);
    for (int8_t i = 0; i < percent/10; i++)
    {
        fputc('.', stdout);
    }
    for (int8_t i = percent/10; i < 10; i++)
    {
        fputc('-', stdout);
    }
    fputc(']', stdout);
    fprintf(stdout, "%2d%%", percent);
    fflush(stdout);
}
int main(int argc, char const *argv[])
{
    for (int8_t i = 0; i < 100; i++)
    {
        show_progress_bar_mini(i); sleep(1);
    }
    puts(""); // flush '\n'
    return 0;
}
