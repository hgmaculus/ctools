/* 13/09/2025 programmers day                                                                           
   destroy file by H. Gabriel Maculus <gabrielmaculus@gmail.com> */                                     
#include <stdio.h>                                                                                      
#include <stdlib.h>                                                                                     
int main(int argc, char *argv[]) {                                                                      
  //printf("Number of arguments: %d\n", argc);                                                          
  puts("Usage: ./destroy_file file_to_destroy whence text-to-insert ");                                 
  if(argc != 4) return 1;                                                                               
  FILE *fp = fopen(argv[1], "r+");                                                                      
  if(!fp) return -1;                                                                                    
  fseek(fp, 0, SEEK_END);                                                                               
  size_t s=ftell(fp); // file size                                                                      
  size_t parm2 = atol(argv[2]);                                                                         
  printf("File size to: %ld\n", s);                                                                     
  if(s < parm2) return 2;                                                                               
  fseek(fp, parm2, SEEK_SET); // printf("Seeking file to: %ld\n", ftell(fp));                           
  printf("Writing %s into %lu position\n", argv[3], ftell(fp));                                         
  fputs(argv[3], fp);                                                                                   
  fclose(fp);                                                                                           
  return 0;                                                                                             
}   
