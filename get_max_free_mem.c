/* get_max_free_mem by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 *
 */

#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _FILE_OFFSET_BITS 64

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

size_t getfreemem() { return sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE); }

int main(int argc, char *argv[])
{
    printf("Page Size: %d\n", getpagesize());

    size_t t = 1024 * 1024 * 1024; // 1GB
    void *ptr = NULL;
    
    
    ptr = malloc(4ll * 1024 * 1024 * 1024); // 4GB
    if (ptr == NULL)
    {
        printf("malloc failed for 4GB\n");
        return 1;
    }
    else
    {
        printf("malloc succeeded for 4GB\n");
    }
    free(ptr);

    // mmap section with 2MB page size
    ptr = mmap(NULL, 1024ll * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_HUGE_2MB, -1, 0); // 1GB
    if (ptr == MAP_FAILED)
    {
        perror("mmap failed for 1GB with 2MB page size");
        return 1;
    }
    else
    {
        printf("mmap succeeded for 1GB with 2MB page size\n");
    }
    munmap(ptr, 1024ll * 1024 * 1024);

    // mmap section fallback to regular page size
    ptr = mmap(NULL, 1024ll * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); // 1GB
    if (ptr == MAP_FAILED)
    {
        perror("mmap failed for 1GB with regular page size");
        return 1;
    }
    else
    {
        printf("mmap succeeded for 1GB with regular page size\n");
    }
    munmap(ptr, 1024ll * 1024 * 1024);

    // mmap section fallback to regular page size
    ptr = mmap(NULL, 4ul * 1024 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_HUGE_2MB, -1, 0); // 4GB
    if (ptr == MAP_FAILED)
    {
        perror("mmap failed for 4GB with 2MB page size");
        return 1;
    }
    else
    {
        printf("mmap succeeded for 4GB with 2MB page size\n");
    }
    munmap(ptr, 4ul * 1024 * 1024 * 1024);
    return 0;
}
