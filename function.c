#include <stdlib.h>
#include <stdio.h>

void hello_world(void) {
  printf("Hello World \n");
}

void p(void (f)(void)) {
  f();
}

void g(void (*f)(void)) {
  (*f)();
}

int main(void) {
  p(hello_world);
  g(&hello_world);
  return 0;
}
