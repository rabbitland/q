#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "qerr.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s file\n", argv[0]);
    return -1;
  }

  char *file_name = argv[1];
  FILE *fd = fopen(file_name, "rb");
  if (!fd) {
    perror("fopen");
    exit(-1);
  }

  fseek(fd, 0, SEEK_END);
  long fsize = ftell(fd);
  fseek(fd, 0, SEEK_SET);

  char *code = malloc(fsize + 1);
  fread(code, fsize, 1, fd);
  fclose(fd);
  code[fsize] = 0;

  TokenArray *tokens_array = tokenize(code, 0);
  if (!tokens_array) {
    qerror();
  }
  parse_tokens(tokens_array, &code);
  freeTokenArray(tokens_array);

  return 0;
}
