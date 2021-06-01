#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  long int *memory_table = malloc(sizeof(long int)*10);
  for (int i = 0; i < 10; ++i) {
    *(memory_table + i) = 0xFF * (i+3) << 8;
  }
  u_int8_t *memtwo = memory_table;
  for (int i = 0; i < 80; ++i) {
    printf("%d\t", i);
    printf("%lx\t", memtwo[i]);
    printf("%lx\n", *(memtwo + i) );
  }
  free(memory_table);
  printf("\n");
}
