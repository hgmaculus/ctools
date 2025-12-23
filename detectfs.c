#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/statfs.h>
#include <stdio.h>

#define BTRFS_SUPER_MAGIC     0x9123683e
#define EXT4_SUPER_MAGIC      0xef53
#define XFS_SUPER_MAGIC       0x58465342

int main(int argc, char *argv[])
{
  if(argc != 2) puts("Usage: detectfs file.dat");
  struct statfs s;
  statfs(argv[1], &s);
  printf("Filesystem type: %lx \n", s.f_type);
  switch (s.f_type) {
    
  case BTRFS_SUPER_MAGIC: {
    printf("BTRFS detected:\n");
    break;
  }
  case XFS_SUPER_MAGIC: {
    printf("XFS detected:\n");
    break;
  }
  case EXT4_SUPER_MAGIC: {
    printf("EXT4 detected:\n");
    break;
  }
  default:
    printf("unknown filesystem:\n");
    break;
  }
  return 0;
}
