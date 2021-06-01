#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ARENA 1 << 20

char *arena;
u_int64_t current;
void hexDump (const char * desc, const void * addr, const int len) {
    int i;
    unsigned char buff[17];
    const unsigned char * pc = (const unsigned char *)addr;

    // Output description if given.

    if (desc != NULL)
        printf ("%s:\n", desc);

    // Length checks.

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    else if (len < 0) {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Don't print ASCII buffer for the "zeroth" line.

            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.

            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII buffer.

    printf ("  %s\n", buff);
}

void *arena_malloc(u_int64_t size) {
  current += size;
  return arena + current - size;
}

void *arena_calloc(u_int64_t size, u_int64_t num) {
  u_int64_t total = size * num;
  current += size;
  return arena + current - size;
}

int compare(const void *a, const void *b) {
  int x = *(const int*)a;
  int y = *(const int*)b;
  return (x > y) - (x < y);
}

struct vector {
  int size;
  int *vector;
};

int main(void) {
  srand(time(0));
  arena = malloc(ARENA);
  current = 0;
  struct vector* vectors = (struct vector*)arena_calloc(sizeof(struct vector), 1);
  vectors[0].size = 10;
  vectors[0].vector = (int*)arena_calloc(sizeof(int), 10);
  for (int i = 0; i < 10; ++i) vectors[0].vector[i] = rand() % 100;
  printf("%ld", vectors[0].size);
  for (int i = 0; i < 10; ++i) printf("%d, ", vectors[0].vector[i]);
  printf("\n");
  hexDump("", arena, current);
  return 0;
}
