#include <stdio.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/types.h>


mode_t file_get_perms(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) != 0)
    {
        perror("file_get_perms: stat failed");
        return (mode_t)-1;
    }
    return st.st_mode;
}
int file_copy_perms(const char *src, const char *dst)
{
    struct stat st;
    if (stat(src, &st) != 0)
    {
        perror("src stat failed");
        return -1;
    }

    if (chmod(dst, st.st_mode) != 0)
    {
        perror("dst chmod failed");
        return -1;
    }

    return 0;
}

int file_create_with_perms(const char *filename, mode_t mode)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror("fopen failed");
        return -1;  
    }
    fclose(f);
    chmod(filename, mode);
    return 0;
}

int file_copy_perms_fd(int src, int dst)
{
    struct stat fst;
    if (fstat(src, &fst) != 0)
    {
        perror("src fstat failed");
        return -1;
    }

    if (fchmod(dst, fst.st_mode) != 0)
    {
        perror("dst fchmod failed");
        return -1;
    }

    return 0;
}

int file_compare_perms(const char *src, const char *dst)
{
    struct stat src_stat, dst_stat;
    if (stat(src, &src_stat) != 0)
    {
        perror("src stat failed");
        return -1;
    }

    if (stat(dst, &dst_stat) != 0)
    {
        perror("dst stat failed");
        return -1;
    }

    if (src_stat.st_mode != dst_stat.st_mode)
    {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    struct stat st;
    stat("/proc/sys/vm/nr_hugepages", &st);

    printf("stat.st_mode: %o\n", st.st_mode);

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <src> <dst>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src)
    {
        perror("fopen src failed");
        return 1;
    }

    FILE *dst = fopen(argv[2], "w");
    if (!dst)
    {
        perror("fopen dst failed");
        return 1;
    }

    if (file_copy_perms(argv[1], argv[2]) != 0)
    {
        fprintf(stderr, "file_copy_perms failed\n");
        return 1;
    }

    if (file_compare_perms(argv[1], argv[2]) != 0)
    {
        fprintf(stderr, "file_compare_perms failed\n");
        return 1;
    }

    return 0;
}