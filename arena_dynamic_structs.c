#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ARENA 4 << 20

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
  if (current > ARENA) {
    printf("Heap overflow");
    exit(0);
  }
  return arena + current - size;
}

void *arena_calloc(u_int64_t size, u_int64_t num) {
  return arena_malloc(size * num);
}

int compare(const void *a, const void *b) {
  int x = *(const int*)a;
  int y = *(const int*)b;
  return (x > y) - (x < y);
}

struct vector {
  int64_t size;
  int64_t *vector;
};

#define TV 120

int main(void) {
  srand(time(0));
  arena = malloc(ARENA);
  current = 0;
  int64_t total_vectors;
  scanf("%ld", &total_vectors);
  printf("%ld", total_vectors);
  struct vector* vectors = (struct vector*)arena_calloc(sizeof(struct vector), total_vectors);
  for (int64_t i = 0; i < total_vectors; ++i) {
    int size = total_vectors; // rand() % TV + (TV >> 1);
    vectors[i].size = size;
    vectors[i].vector = (int64_t*)arena_calloc(sizeof(int64_t), size);
    for (int64_t j = 0; j < size; ++j) {
      vectors[i].vector[j] = (int64_t)rand();
      vectors[i].vector[j] <<= 32;
      vectors[i].vector[j] |= (int64_t)rand();
    }
  }

  for (int64_t i = 0; i < total_vectors; ++i) {
    //printf("Enter character to go to next\n");
    //printf("Vector: %ld\t Size: %ld\n", i, vectors[i].size);
    for (int64_t j = 0; j < vectors[i].size; ++j) {
     //printf("%ld, ", vectors[i].vector[j]);
    }
    //printf("\n");
  }
  //hexDump("", arena, current);
  free(arena);
  printf("%ld\n", current);
}
