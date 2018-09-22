#include <stdlib.h>
#include <stdio.h>
#include "token.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: q file\n");
    return -1;
  }

  char *file_name = argv[1];
  printf("%s\n", file_name);

  FILE *fd = fopen(file_name, "rb");
  fseek(fd, 0, SEEK_END);
  long fsize = ftell(fd);
  fseek(fd, 0, SEEK_SET);

  char *code = malloc(fsize + 1);
  fread(code, fsize, 1, fd);
  fclose(fd);
  code[fsize] = 0;

  TokenArray *tokens_array = tokenize(code, 0);
  printf("Number of tokens: %zu\n", tokens_array->count);
  for (int i = 0; i < tokens_array->count; ++i) {
    printToken(&tokens_array->tokens[i], &code);
  }
  freeTokenArray(tokens_array);

  return 0;
}
