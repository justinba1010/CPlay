/*
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNK 8

struct stringy {
  char *string;
  size_t size;
};

void freestringy(struct stringy s) {
  if (s.string != NULL) {
    free(s.string);
  }
}

struct stringy read_string() {
  char *input = NULL;
  char tempbuf[CHUNK];
  size_t inputlen = 0;
  size_t templen = 0;
  do {
    fgets(tempbuf, CHUNK, stdin);
    templen = strlen(tempbuf);
    input = realloc(input, inputlen + templen + 1);
    strcpy(input + inputlen, tempbuf);
    inputlen += templen;
  } while (templen == CHUNK - 1 && tempbuf[CHUNK-2] != '\n');
  struct stringy s;
  s.string = input;
  s.size = inputlen;
  return s;
}

char *readinput(size_t *size) {
  char *input = NULL;
  char tempbuf[CHUNK];
  size_t inputlen = 0;
  size_t templen = 0;
  do {
    fgets(tempbuf, CHUNK, stdin);
    templen = strlen(tempbuf);
    input = realloc(input, inputlen + templen + 1);
    strcpy(input + inputlen, tempbuf);
    inputlen += templen;
  } while (templen == CHUNK - 1 && tempbuf[CHUNK-2] != '\n');
  *size = inputlen;
  return input;
}

int main(void) {
  char *result;
  size_t *size;
  struct stringy s;
  size = malloc(sizeof(size_t));
  result = readinput(size);
  printf("Result: %s", result);
  printf("Length: %d\n", *size);
  free(result);
  result = readinput(size);
  printf("Result: %s", result);
  printf("Length: %d\n", *size);
  free(result);
  free(size);
  s = read_string();
  printf("Result: %s", s.string);
  printf("Length: %d\n", s.size);
  freestringy(s);
  return 0;
}
