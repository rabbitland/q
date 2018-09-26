#include <stdio.h>
#include "token.h"

void parse_tokens(TokenArray *tokens, char **code) {
  printf("Number of tokens: %zu\n", tokens->count);
  for (int i = 0; i < tokens->count; ++i) {
    printToken(&tokens->tokens[i], code);
  }
}
