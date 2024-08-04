// H. Gabriel Maculus <gabrielmaculus@gmail.com>
#include <stdio.h>

typedef void (*functype)();

void h1() { printf("H1\n"); }
void h2() { printf("H2\n"); }
void h3() { printf("H3\n"); }
functype funcs[] = { h1, h2, h3 };
functype f1() { return h1; }
int main(int argc, char *argv[])
{
  void (*selector)() = f1();
  selector();
  return 0;
}
/*
  Aunque no es muy sencillo, es lo mas que pude reducir un ejemplo
  de funciones que devuelven punteros a funciones.
  Una llamada a la funcion f1() devuelve un puntero a h1.
  Una llamada a selector() ejecuta h1()
*/
