#ifndef __Q_PARSER__
#define __Q_PARSER__

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define FOREACH_KIND(KIND) \
  KIND(ImportStatemnetKind) \

enum NodeKind {
  FOREACH_KIND(GENERATE_ENUM)
};

static char *KIND_STRINGS[] = {
  FOREACH_KIND(GENERATE_STRING)
};

struct ImportStatemnet {
  char *module_name;
};

struct VariableDeclaration {
  char *name;
  // TODO(qti3e) Expression.
};

struct Node {
  enum NodeKind kind;
  size_t length; // Number of tokens for this Node.
  union {
    struct ImportStatemnet import_statemnet;
    struct VariableDeclaration variable_declaration;
  } data;
} typedef Node;

struct NodeArray {
  size_t count;
  size_t length; // sumof(this.nodes[x].length)
  Node nodes[];
} typedef NodeArray;

NodeArray* parse_tokens(TokenArray *tokens, char **code);

NodeArray* source_file(TokenArray *tokens, char **code, size_t cursor);
Node *import_statemnet(TokenArray *tokens, char **code, size_t cursor);

#endif
