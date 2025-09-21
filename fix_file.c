/* Mini fix file compare by H. Gabriel Máculus <gabrielmaculus@gmail.com>                                                                                               
 *                                                                                                                                                                      
 */                                                                                                                                                                     
#include <stdio.h>                                                                                                                                                      
                                                                                                                                                                        
int fix_file(const char *sname, const char *dname){                                                                                                                     
  FILE *s = fopen(sname, "r");                                                                                                                                          
  FILE *d = fopen(dname, "r+");                                                                                                                                         
                                                                                                                                                                        
  if(!s) {                                                                                                                                                              
    fclose(d);                                                                                                                                                          
    return -1; // -1 source not found or can't read                                                                                                                     
  }                                                                                                                                                                     
  if(!d){                                                                                                                                                               
    fclose(s);                                                                                                                                                          
    return -2; // -2 destination not found or can't read                                                                                                                
  }                                                                                                                                                                     
                                                                                                                                                                        
  {                                                                                                                                                                     
    char sa, db;                                                                                                                                                        
    while(!feof(s) && !feof(d)) {                                                                                                                                       
      sa = fgetc(s);                                                                                                                                                    
      db = fgetc(d);                                                                                                                                                    
      if(sa != db ) { // difference                                                                                                                                     
        printf("Found difference at: %ld\n", ftell(s));                                                                                                                 
        fseek(d, -1, SEEK_CUR);                                                                                                                                         
        fputc(sa, d);                                                                                                                                                   
      }                                                                                                                                                                 
                                                                                                                                                                        
                                                                                                                                                                        
    }                                                                                                                                                                   
    if(feof(s) && feof(d)) return 0;                                                                                                                                    
    else {                                                                                                                                                              
      fclose(s);                                                                                                                                                        
      fclose(d);                                                                                                                                                        
    }                                                                                                                                                                   
  }                                                                                                                                                                     
                                                                                                                                                                        
  return -1;                                                                                                                                                            
}                                                                                                                                                                       
int main(int argc, char *argv[])                                                                                                                                        
{                                                                                                                                                                       
  if(argc != 3) return -3;                                                                                                                                              
                                                                                                                                                                        
  return fix_file(argv[1], argv[2]);                                                                                                                                    
} 
