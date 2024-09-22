// H. Gabriel Maculus <gabrielmaculus@gmail.com>

#ifndef _STDGM_H
#define _STDGM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#define array_size(arr) (sizeof(arr) / sizeof((arr)[0]))

#define out(s) fputs(s, stdout)

typedef int (*printf_p)(const char *cad, ...);
typedef int (*pf)();
typedef pf arrayfp[];
printf_p p = printf;

// return false if file not exist, or true if file exists
bool fileexist(const char *filename) {
  FILE *f = fopen(filename, "r");
  bool r = f ? true : false;
  if(f) fclose(f);
  return r;
}

size_t filesize(const char *filename) {
  size_t fsize=0;
  FILE *f = fopen(filename, "r");
  if(!f) {
    fprintf(stderr, "filesize(): file not found %s\n", filename);
    return 0;
  }
  fseek(f, 0, SEEK_END);
  fsize = ftell(f);
  fclose(f);
  return fsize;
}


// Seccion cadenas, funciones para manipulacion de cadenas

// Concatena la cadena apuntada por src al final de la cadena dst
int stringconcat(char *dst, char *src) {
  while(*dst != '\0'){ dst++; }// encuentra el final de la cadena
  while(*src != '\0'){
    *dst = *src;
    src++;
    dst++;
  }
  *dst = '\0';
  return 0;
}

// Determina el tamano de una cadena
size_t stringsize(const char *restrict word) {
  size_t count=0;
  while(*word != '\0') {
    word++;
    count++;
  }
  return count;
}

int stringcopy(const char *restrict src, char *restrict dst) {
  while(*src != '\0') {
    *dst = *src;
    src++;
    dst++;
  }
  dst++;
  *dst = '\0';
  return 0;
}

// Encuentra en que posicion (byte) del archivo se encuentra la palabra _word_
size_t stringfind(const char *restrict word, FILE *restrict fd) {
  size_t location=0;
  size_t ws = stringsize(word);
  size_t word_count=0;
  char c;
  while (!feof(fd)) {
    c=fgetc(fd);
    if(c == *word) { // primera coincidencia
      location = ftell(fd); // guarda la ubicacion de la primera coincidencia
      const char *restrict target = word;
      word_count++;
      for(size_t i=1; i < ws; i++) { // iniciar busqueda de palabra completa
	c = fgetc(fd);
	target++;
	if(c == *target) {
	  word_count++;
	  if(word_count == ws) return location;
	} else {
	  word_count=0;
	  break; // cancela busqueda, no coincide 
	}
      }
    }
  }
  return location;
}

// Seccion caracteres, funciones para manipulacion de caracteres
/* lee una tecla presionada sin mostrar en la salida estandar */
int getch(void) {
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

/* lee una tecla presionada y la muestra en la salida estandar */
int getche(void) {
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

/* Lee una secuencia de hasta n caracteres y 
lo guarda en la cadena apuntada por str, si 
se ingresa el caracter de stop sale inmediatamente
La cadena apuntada por str debe ser mayor que n
*/
void stringgete(char *str, size_t n, char stop) {
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    while(n) {
        *str = getchar();
        if(*str == stop) break;
        str++;
        n--;
    }
    *str = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}
/* Lee una secuencia de hasta n caracteres y
lo guarda en la cadena apuntada por str, si
se ingresa el caracter de stop sale inmediatamente
Sin mostrar los caracteres ingresados en la pantalla,
se usa para el ingreso de datos sensibles

*/
void stringget(char *str, size_t n, char stop) {
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    while (n) {
        *str = getchar();
        if (*str == stop)
            break;
        str++;
        n--;
    }
    *str = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}

int compare2files(const char *sname, const char *dname){
  FILE *s = fopen(sname, "r");
  FILE *d = fopen(dname, "r");

  if(!s) {
    fclose(d);
    return -1; // -1 source not found or can't read
  }
  if(!d){
    fclose(s);
    return -2; // -2 destination not write permission or can't write
  } 

  {
    char sa, db;
    while(!feof(s) && !feof(d)) {
      sa = fgetc(s);
      db = fgetc(d);
      if(sa != db ) break;
    }
    if(feof(s) && feof(d)) return 0;
    else return -1;
  }

  fclose(s);
  fclose(d);	
}

char int2char(int a) { return (char)a; }
char long2char(long a) { return (char)a; }

int inci(int i) { if((i+1) > i) ++i; return i; }
long int incl(long int i) { if((i+1) > i) ++i; return i; }
size_t incs(size_t i) { if((i+1) > i) ++i; return i; }

#endif
