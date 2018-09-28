#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "token.h"
#include "parser.h"

void print_node(Node *node) {
  printf(">> Node\tKIND: %s\n", KIND_STRINGS[node->kind]);
}

NodeArray* parse_tokens(TokenArray *tokens, char **code) {
  return source_file(tokens, code, 0);
} 

NodeArray* source_file(TokenArray *tokens, char **code, size_t cursor) {
  Node *tmp_node;
  Node *node = NULL;
  size_t node_length = 0;

  size_t node_array_size = offsetof(NodeArray, nodes);
  void *childs = malloc(node_array_size);
  size_t count = 0; // Number of nodes in the array.
  size_t length = 0; // number of tokens in the array. == tokens->count

  do {
    if (node) {
      // Insert node to the array.
      count += 1;
      length += node_length;
      childs = realloc(childs, node_array_size + count * sizeof(Node));
      memcpy(childs + node_array_size + (count - 1) * sizeof(Node), &node, sizeof(Node));
      cursor += node_length;
      // Debug...
      print_node(node);
      // Reset data
      node = NULL;
      node_length = 0;
    }

    if (tokens->tokens[cursor].type == LINE_BREAK) {
      cursor += 1;
      continue;
    }

    printToken(&tokens->tokens[cursor], code);

    tmp_node = import_statemnet(tokens, code, cursor);
    if (tmp_node && tmp_node->length > node_length) {
      node = tmp_node;
      node_length = node->length;
    }

    if (!node) {
      printf("Unecpected token `%s`.\n",
          tokenName(&tokens->tokens[cursor]));
      exit(-1);
    }
  } while(1);

  NodeArray *ret = childs;
  ret->count = count;
  ret->length = length;
  return childs;
}

Node *import_statemnet(TokenArray *tokens, char **code, size_t cursor) {
  if (tokens->tokens[cursor].type != USE_KEYWORD) return NULL;
  if (tokens->tokens[cursor + 1].type != COLON_COLON) return NULL;
  if (tokens->tokens[cursor + 2].type != IDENTIFIER) return NULL;
  if (tokens->tokens[cursor + 3].type != SEMICOLON) return NULL;
  char *module_name = tokenData(&tokens->tokens[cursor + 2], code);
  Node *node = malloc(sizeof(Node));
  node->kind = ImportStatemnetKind;
  node->length = 4;
  node->data.import_statemnet = (struct ImportStatemnet){
    module_name
  };
  return node;
}
