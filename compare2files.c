/* Mini file compare by H. Gabriel Máculus <gabrielmaculus@gmail.com>
 * 
*/
#include <stdio.h>

int compare2files(const char *sname, const char *dname){
  FILE *s = fopen(sname, "r");
  FILE *d = fopen(dname, "r");

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
      if(sa != db ) break;
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
  
  return compare2files(argv[1], argv[2]);
}
