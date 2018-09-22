#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

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

char *tokenData(Token *token, char **code) {
  // Skip characters to the start.
  char *data = *code + token->start;
  // Allocate memory and copy the substr into it.
  void *ptr = malloc(token->len + 1);
  memset(ptr + token->len, 0x00, 1);
  strncpy(ptr, data, token->len);
  return ptr;
}

char* tokenName(Token *token) {
  switch (token->type) {
    case IDENTIFIER:
      return "IDENTIFIER";
    case KEYWORD:
      return "KEYWORD";
    case COMMENT:
      return "COMMENT";
    case NUMERIC_LITERAL:
    case STRING_LITERAL:
      return "LITERAL";
    case OPEN_PARENTHESIS:
    case CLOSE_PARENTHESIS:
      return "PARENTHESIS";
    case OPEN_BRACE:
    case CLOSE_BRACE:
      return "BRACE";
    case OPEN_BRACKET:
    case CLOSE_BRACKET:
      return "BRACKET";
    case LINE_BREAK:
      return "LINE_BREAK";
    default:
      return "OPERATOR";
  }
}

void printToken(Token *token, char **code) {
  char *data = tokenData(token, code);
  if (token->type == LINE_BREAK) {
    data = "\\n";
  }
  printf(
      ">> pos:\t%d \ttype[%02d]: %s \tdata: <%s>\n",
      token->start,
      token->type,
      tokenName(token),
      data);
  if (token->type != LINE_BREAK) {
    free(data);
  }
}

void freeTokenArray(TokenArray *t) {
  free(t);
}

TokenArray *tokenize(char *code, int skip_comments) {
  int num_tokens = 0;
  // size = token_array_size + num_tokens * sizeof(Token);
  size_t token_array_size = offsetof(TokenArray, tokens);
  void *tokens = malloc(token_array_size);
  // Temporary token.
  Token token;
  // Flag to check if we should insert token into tokens or not.
  int insert_token = 0;
  
  // Current position in the code.
  int cursor = 0;
  // Current character under the cursor.
  char c;
  char next_char;

  do {
    if (insert_token) {
      if (token.type != COMMENT || !skip_comments) {
        // Insert `token` to tokens.
        ++num_tokens;
        tokens = realloc(tokens, token_array_size + num_tokens * sizeof(Token));
        memcpy(token_array_size + tokens + (num_tokens - 1) * sizeof(Token), &token, sizeof(Token));
      }
      // Read the next characters.
      cursor += token.len;
      insert_token = 0;
    }

    c = code[cursor];
    next_char = code[cursor + 1];
    if (c == 0x00) break;

    // Handle LINE_BREAK.
    if (c == 0x0A) {
      // Create the token.
      token.type = LINE_BREAK;
      token.start = cursor;
      token.len = 1;
      insert_token = 1;
      continue;
    }

    // Skip white spaces.
    if (isspace(c)) {
      cursor++;
      continue;
    }

    // Handle NUMERIC_LITERAL
    if (isdigit(c)) {
      token.type = NUMERIC_LITERAL;
      token.start = cursor;
      token.len = 0;
      insert_token = 1;
      // Look for end of the number.
      while (c != 0x00 && isdigit(c)) {
        c = code[cursor + token.len + 1];
        ++token.len;
      }
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
    if (c == '/' && next_char == '/') {
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
      // Default to IDENTIFIER
      token.type = IDENTIFIER;
      token.start = cursor; insert_token = 1;
      char* identifier = tokenData(&token, &code);
      size_t n = sizeof(KEYWORDS)/sizeof(KEYWORDS[0]);
      for (int i = 0; i < n; ++i) {
        if (strcmp(identifier, KEYWORDS[i]) == 0) {
          token.type = KEYWORD;
          break;
        }
      }
      free(identifier);
      continue;
    }

    // Now look for tokens with a fixed size.
    token.start = cursor;
    insert_token = 1;

two_byte:
    // -- Two byte tokens
    token.len = 2;

    // If it's the last character, jump to check
    // one byte tokens.
    if (next_char == 0x00) goto one_byte;

    if (next_char == '=') {
      switch (c) {
        case '=': token.type = EQUALITY; continue;
        case '!': token.type = INEQUALITY; continue;
        case '|': token.type = BIT_OR_ASSIGN; continue;
        case '^': token.type = BIT_XOR_ASSIGN; continue;
        case '~': token.type = BIT_NOT_ASSIGN; continue;
        case '&': token.type = AND_ASSIGN; continue;
        case '+': token.type = PLUS_ASSIGN; continue;
        case '-': token.type = MINUS_ASSIGN; continue;
        case '*': token.type = TIMES_ASSIGN; continue;
        case '/': token.type = DIV_ASSIGN; continue;
        case '>': token.type = GREATER_THAN_EQUAL; continue;
        case '<': token.type = LESS_THAN_EQUAL; continue;
      }
    }

    if (c == '.' && next_char == '.') { token.type = DOT_DOT; continue; }
    if (c == '|' && next_char == '|') { token.type = LOGICAL_OR; continue; }
    if (c == '&' && next_char == '&') { token.type = LOGICAL_AND; continue; }
    if (c == '<' && next_char == '<') { token.type = LEFT_SHIFT; continue; }
    if (c == '>' && next_char == '>') { token.type = RIGHT_SHIFT; continue; }
    if (c == '+' && next_char == '+') { token.type = INCREMENT; continue; }
    if (c == '-' && next_char == '-') { token.type = DECREMENT; continue; }

one_byte:
    // -- One byte tokens
    token.len = 1;

    if (c == '.') { token.type = DOT; continue; }
    if (c == '(') { token.type = OPEN_PARENTHESIS; continue; }
    if (c == ')') { token.type = CLOSE_PARENTHESIS; continue; }
    if (c == '{') { token.type = OPEN_BRACE; continue; }
    if (c == '}') { token.type = CLOSE_BRACE; continue; }
    if (c == '[') { token.type = OPEN_BRACKET; continue; }
    if (c == ']') { token.type = CLOSE_BRACKET; continue; }
    if (c == ';') { token.type = SEMICOLON; continue; }
    if (c == ':') { token.type = SEMICOLON; continue; }
    if (c == ',') { token.type = COMMA; continue; }
    if (c == '=') { token.type = ASSIGNMENT; continue; }
    if (c == '|') { token.type = BIT_OR; continue; }
    if (c == '&') { token.type = BIT_AND; continue; }
    if (c == '^') { token.type = BIT_XOR; continue; }
    if (c == '~') { token.type = BIT_NOT; continue; }
    if (c == '!') { token.type = NOT; continue; }
    if (c == '+') { token.type = PLUS; continue; }
    if (c == '-') { token.type = MINUS; continue; }
    if (c == '*') { token.type = TIMES; continue; }
    if (c == '/') { token.type = DIV; continue; }
    if (c == '>') { token.type = GREATER_THAN; continue; }
    if (c == '<') { token.type = LESS_THAN; continue; }

    // TODO(qti3e) Error <UNEXPECTED_CHARACTER>
    // But for now let's just skip this unknown character:
    printf("Error! %d %d [%c]\n", cursor, c, c);
    return NULL;
  } while (1);

  TokenArray *ret = tokens;
  ret->count = num_tokens;

  return ret;
}
