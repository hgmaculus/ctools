/* copy file using sendfile kernel sys call
    by H. Gabriel Maculus gabrielmaculus@gmail.com
    
*/
#include <sys/sendfile.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(argc != 3) {
        puts("Usage: copy_sendfile source_file destination_file");
        return -1;
    }

    int source = open(argv[1], O_RDONLY);
    if(source == -1) {
        puts("source not found");
        return -2;
    }
    struct stat fs_stat;
    fstat(source, &fs_stat);

    int destination = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, fs_stat.st_mode);
    if(destination == -1) {
        puts("destination not found");
        return -3;
    }
    size_t source_size = lseek(source, 0, SEEK_END);
    //printf("source_size: %ul\n", source_size);
    lseek(source, 0, SEEK_SET);
    int ret = sendfile(destination, source, 0, source_size);
    if(ret == -1) {
        puts("sendfile: failed");
        return -4;
    }
    close(destination);
    close(source);
    return 0;
}
