#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "token.h"
#include "parser.h"
#include "qerr.h"

#define EXPECT_TOKEN(tokens, cursor, pos, token, priority) \
  if (tokens->tokens[cursor + pos].type != token) { \
    error(priority, tokens->tokens[cursor + pos].start, \
        tokens->tokens[cursor + pos].type, token); \
    return NULL; \
  }

void print_node(Node *node) {
  printf(">> Node\tKIND: %s\n", KIND_STRINGS[node->kind]);
}

int last_priority = -1;
void error(int priority, int pos, int actual, int excpected) {
  if (priority >= last_priority) {
    last_error.code = UNEXCPECTED_TOKEN;
    last_error.data.unexcpected_token = (struct UNEXCPECTED_TOKEN){
      pos, actual, excpected
    };
  }
}

NodeArray* parse_tokens(TokenArray *tokens, char **code) {
  return source_file(tokens, code, 0);
} 

NodeArray* source_file(TokenArray *tokens, char **code, size_t cursor) {
  clear_error();

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
      return NULL;
    }
  } while(1); 
  clear_error();

  NodeArray *ret = childs;
  ret->count = count;
  ret->length = length;
  return childs;
}

Node *import_statemnet(TokenArray *tokens, char **code, size_t cursor) {
  EXPECT_TOKEN(tokens, cursor, 0, USE_KEYWORD, 0);
  EXPECT_TOKEN(tokens, cursor, 1, COLON_COLON, 1);
  EXPECT_TOKEN(tokens, cursor, 2, IDENTIFIER, 2);
  EXPECT_TOKEN(tokens, cursor, 3, SEMICOLON, 2);

  char *module_name = tokenData(&tokens->tokens[cursor + 2], code);
  Node *node = malloc(sizeof(Node));
  node->kind = ImportStatemnetKind;
  node->length = 4;
  node->data.import_statemnet = (struct ImportStatemnet){
    module_name
  };
  return node;
}
