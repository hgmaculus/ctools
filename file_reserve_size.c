#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/statfs.h>
#include <stdio.h>

#define BTRFS_SUPER_MAGIC 0x9123683e
#define EXT4_SUPER_MAGIC 0xef53
#define XFS_SUPER_MAGIC 0x58465342

size_t file_size(const char *filename)
{
  FILE *f = fopen(filename, "r");
  if (!f)
  {
    fprintf(stderr, "file_size(): file not found %s\n", filename);
    return 0;
  }

  fseek(f, 0, SEEK_END);
  size_t fsize = ftell(f);
  fclose(f);
  return fsize;
}

size_t file_reserve_size(const char *filename, size_t size)
{
  FILE *f = fopen(filename, "w");
  if (!f)
  {
    fprintf(stderr, "file_reserve_size(): file not found %s\n", filename);
    return 0;
  }
  struct statfs s;
  statfs(filename, &s);
  // printf("Filesystem type: %lx \n", s.f_type);
  int fd = fileno(f);
  switch (s.f_type)
  {

  case EXT4_SUPER_MAGIC:
  case XFS_SUPER_MAGIC:
  case BTRFS_SUPER_MAGIC:
  {
    if (fallocate(fd, 0, 0, size) != 0)
    {
      fprintf(stderr, "file_reserve_size(): fallocate failed %s\n", filename);
      fclose(f);
      return 0;
    }
    else
    {
      printf("file_reserve_size(): fallocate success %s\n", filename);
    }
    break;
  }

  default:
    printf("Unknown filesystem: fallocate not supported\n");
    break;
  }

  fclose(f);

  // check if the file size is correct

  if (file_size(filename) != size)
  {
    fprintf(stderr, "file_reserve_size(): file size mismatch %s\n", filename);
    return 0;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    puts("Usage: file_reserve_size file.dat");
    return 1;
  }

  size_t size = 1024 * 1024 * 1024; // 1GB
  file_reserve_size(argv[1], size);
  return 0;
}
