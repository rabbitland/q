#include <stdio.h>
#include <stdlib.h>
#include "token.h"

enum NodeKind {
  ImportStatemnet,
  VariableDeclaration,
};

struct ImportStatemnet {
  char *module_name;
};

struct VariableDeclaration {
  int x;
};

struct Node {
  enum NodeKind kind;
  union Data {
    struct ImportStatemnet import_statemnet;
    struct VariableDeclaration variable_declaration;
  } data;
} typedef Node;

void parse_tokens(TokenArray *tokens, char **code) {
  printf("Number of tokens: %zu\n", tokens->count);
  for (int i = 0; i < tokens->count; ++i) {
    printToken(&tokens->tokens[i], code);
  }

  void *nodes = malloc(0);
  int cursor = 0;

  while (cursor < tokens->count) {
    if (tokens->tokens[cursor].type == USE_KEYWORD) {
      if (tokens->tokens[cursor + 1].type == COLON_COLON) {
        printf("Import!!!\n");
        exit(1);
      }
      printToken(&tokens->tokens[cursor], code);
      exit(-1);
    }
  }
}
