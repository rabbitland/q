#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum TokenType {
  STRING_LITERAL,
  IDENTIFIER,
  OPEN_PARENTHESIS,
  CLOSE_PARENTHESIS,
  OPEN_BRACE,
  CLOSE_BRACE,
  OPEN_BRACKET,
  CLOSE_BRACKET,
  COMMENT,
  LINE_BREAK,
  SEMICOLON,
  COLON, // :
  COMMA, // ,
  DOT,
  DOT_DOT,
  // TODO(qti3e)
  KEYWORD,
  // TODO(qti3e) Maybe remove this and instead add an
  // enum member for each OPERATOR?
  OPERATOR,
  NUMBER_LITERAL,
};

struct Token {
  enum TokenType type;
  char **code;
  int start;
  int len;
} typedef Token; 


char* KEYWORDS[] = {
  // CONTROL FLOW 
  "if", "while", "for",
  // TYPES
  "int", "void", "string", "null",
  // Q
  "chan", "thread", "pipe",
  // RESERVED
  "public", "private", "protected", "class",
  // TODO(qti3e)
};

char* OPERATORS[] = {
  "||",
  "&&",
  "==",
  "|=",
  "^=",
  "!=",
  "~=",
  "&=",
  "+=",
  "-=",
  "*=",
  "/=",
  "<=",
  ">=",
  "<<",
  ">>",
  "++",
  "--",
  "|",
  "&",
  "=",
  "^",
  "!",
  "~",
  "+",
  "-",
  "*",
  "/",
  "<",
  ">",
};

char *tokenData(Token *token) {
  // Skip characters to the start.
  char *data = *token->code + token->start;
  // Allocate memory and copy the substr into it.
  void *ptr = malloc(token->len);
  strncpy(ptr, data, token->len);
  return ptr;
}

void printToken(Token *token) {
  int print_data = 1;
  printf("{ pos: %d, type: ", token->start);
  switch (token->type) {
    case OPERATOR:
      printf("OPERATOR");
      break;
    case NUMBER_LITERAL:
      printf("NUMBER_LITERAL");
      break;
    case STRING_LITERAL:
      printf("STRING_LITERAL");
      break;
    case IDENTIFIER:
      printf("IDENTIFIER");
      break;
    case KEYWORD:
      printf("KEYWORD");
      break;
    case OPEN_PARENTHESIS:
      printf("OPEN_PARENTHESIS");
      print_data = 0;
      break;
    case CLOSE_PARENTHESIS:
      printf("CLOSE_PARENTHESIS");
      print_data = 0;
      break;
    case OPEN_BRACE:
      printf("OPEN_BRACE");
      print_data = 0;
      break;
    case CLOSE_BRACE:
      printf("CLOSE_BRACE");
      print_data = 0;
      break;
    case OPEN_BRACKET:
      printf("OPEN_BRACKET");
      print_data = 0;
      break;
    case CLOSE_BRACKET:
      printf("CLOSE_BRACKET");
      print_data = 0;
      break;
    case COMMENT:
      printf("COMMENT");
      break;
    case LINE_BREAK:
      printf("LINE_BREAK");
      print_data = 0;
      break;
    case SEMICOLON:
      printf("SEMICOLON");
      print_data = 0;
      break;
    case COLON:
      printf("COLON");
      print_data = 0;
      break;
    case COMMA:
      printf("COMMA");
      print_data = 0;
      break;
    case DOT:
      printf("DOT");
      print_data = 0;
      break;
    case DOT_DOT:
      printf("DOT_DOT");
      print_data = 0;
      break;
  }
  if (print_data) {
    char *data = tokenData(token);
    printf(", data: \"%s\" }\n", data);
    free(data);
  } else {
    printf(" }\n");
  }
}

int main() {
  char *code = "x = 3;\n// test \nvar = 32 + x * 4; DA = 'Hello World'; c = 's\\' s'";
  printf("Code:\n%s\n", code);

  int num_tokens = 0;
  // size = num_tokens * sizeof(Token) + 1;
  // `tokens` is zero terminated so we allocate one more byte for it.
  void *tokens = malloc(1);
  // Temporary token.
  Token token;
  token.code = &code;
  // Flag to check if we should insert token into tokens or not.
  int insert_token = 0;
  
  // Current position in the code.
  int cursor = 0;
  // Current character under the cursor.
  char c;

  int skip_comments = 0;

  do {
    if (insert_token) {
      if (token.type != COMMENT || !skip_comments) {
        // Insert `token` to tokens.
        ++num_tokens;
        tokens = realloc(tokens, num_tokens * sizeof(Token) + 1);
        memcpy(tokens + (num_tokens - 1) * sizeof(Token), &token, sizeof(Token));
        memset(tokens + num_tokens * sizeof(Token), 0x00, 1);
      }
      // Read the next characters.
      cursor += token.len;
      insert_token = 0;
    }

    c = code[cursor];
    if (c == 0x00) break;

    // Skip white spaces.
    if (isspace(c)) {
      cursor++;
      continue;
    }

    // Handle LINE_BREAK.
    if (c == 0x0A) {
      // Create the token.
      token.type = LINE_BREAK;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle STRING_LITERAL
    if (c == '\'' || c == '"') {
      char mark = c;
      int escape = 0;
      token.len = 0;
      while (c != 0x00) {
        c = code[cursor + token.len + 1];
        ++token.len;
        if (c == '\\') {
          escape = !escape;
        }
        if (c == mark && !escape) {
          ++token.len;
          break;
        }
        if (c != '\\') {
          escape = 0;
        }
      }
      token.type = STRING_LITERAL;
      token.start = cursor;
      insert_token = 1;
      continue;
    }

    // Handle COMMENT
    if (c == 0x2F && code[cursor + 1] == 0x2F) {
      token.len = 0;
      while (c != 0x0A && c != 0x00) {
        c = code[cursor + token.len + 1];
        ++token.len;
      }
      token.type = COMMENT;
      token.start = cursor;
      insert_token = 1;
      continue;
    }

    // Handle IDENTIFIER & KEYWORD
    if (isalpha(c)) {
      token.len = 0;
      while (isalnum(c) && c != 0x00) {
        c = code[cursor + token.len + 1];
        ++token.len;
      }
      // Create the token.
      // TODO(qti3e) Check if this is a keyword or not.
      token.type = IDENTIFIER;
      token.start = cursor;
      insert_token = 1;
      continue;
    }

    // Handle DOT_DOT
    if (c == '.' && code[cursor + 1] == '.') {
      token.type = DOT_DOT;
      token.start = cursor;
      token.len = 2;
      insert_token = 1;
      continue;
    }

    // Handle DOT
    if (c == '.') {
      token.type = DOT;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle OPEN_PARENTHESIS
    if (c == '(') {
      token.type = OPEN_PARENTHESIS;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle CLOSE_PARENTHESIS
    if (c == ')') {
      token.type = CLOSE_PARENTHESIS;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle OPEN_BRACKET
    if (c == '[') {
      token.type = OPEN_BRACKET;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle CLOSE_BRACKET
    if (c == ']') {
      token.type = CLOSE_BRACKET;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle OPEN_BRACE
    if (c == '{') {
      token.type = OPEN_BRACE;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle CLOSE_BRACE
    if (c == '}') {
      token.type = CLOSE_BRACE;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle SEMICOLON
    if (c == ';') {
      token.type = SEMICOLON;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle COLON
    if (c == ':') {
      token.type = SEMICOLON;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Handle COMMA
    if (c == ',') {
      token.type = COMMA;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // TODO(qti3e) Error <UNEXPECTED_CHARACTER>
    // But for now let's just skip this unknown character:
    cursor++;
  } while (1);

  printf("\nTokens:\n");
  for (int i = 0; ; i += sizeof(Token)) {
    char *x = tokens + i;
    if (x[0] == 0x00) {
      break;
    }
    printToken(tokens + i);
  }

  free(tokens);
}
