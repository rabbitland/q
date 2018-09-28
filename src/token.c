#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

char* KEYWORDS[] = {
  // CONTROL FLOW 
  "if", "while", "for", "break", "continue",
  "return", "switch", "case", "use", "var",
  "print"
  // INTERNAL TYPES
  "int", "void", "string", "null"
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

// TODO(qti3e) This is ugly, we can use a macro
// to generate an enum and an array of chars containg
// each enum name.
char* tokenName(Token *token) {
  switch (token->type) {
    case LINE_BREAK:
      return "LINE_BREAK";
    case NUMERIC_LITERAL:
      return "NUMERIC_LITERAL";
    case STRING_LITERAL:
      return "STRING_LITERAL";
    case COMMENT:
      return "COMMENT";
    case IDENTIFIER:
      return "IDENTIFIER";
    case START_OF_KEYWORDS:
      return "START_OF_KEYWORDS";
    case IF_KEYWORD:
      return "IF_KEYWORD";
    case WHILE_KEYWORD:
      return "WHILE_KEYWORD";
    case FOR_KEYWORD:
      return "FOR_KEYWORD";
    case BREAK_KEYWORD:
      return "BREAK_KEYWORD";
    case CONTINUE_KEYWORD:
      return "CONTINUE_KEYWORD";
    case RETURN_KEYWORD:
      return "RETURN_KEYWORD";
    case SWITCH_KEYWORD:
      return "SWITCH_KEYWORD";
    case CASE_KEYWORD:
      return "CASE_KEYWORD";
    case USE_KEYWORD:
      return "USE_KEYWORD";
    case VAR_KEYWORD:
      return "VAR_KEYWORD";
    case PRINT_KEYWORD:
      return "PRINT_KEYWORD";
    case INT_KEYWORD:
      return "INT_KEYWORD";
    case VOID_KEYWORD:
      return "VOID_KEYWORD";
    case STRING_KEYWORD:
      return "STRING_KEYWORD";
    case NULL_KEYWORD:
      return "NULL_KEYWORD";
    case END_OF_KEYWORDS:
      return "END_OF_KEYWORDS";
    case COLON_COLON:
      return "COLON_COLON";
    case DOT_DOT:
      return "DOT_DOT";
    case EQUALITY:
      return "EQUALITY";
    case INEQUALITY:
      return "INEQUALITY";
    case LOGICAL_OR:
      return "LOGICAL_OR";
    case LOGICAL_AND:
      return "LOGICAL_AND";
    case BIT_OR_ASSIGN:
      return "BIT_OR_ASSIGN";
    case BIT_XOR_ASSIGN:
      return "BIT_XOR_ASSIGN";
    case BIT_NOT_ASSIGN:
      return "BIT_NOT_ASSIGN";
    case AND_ASSIGN:
      return "AND_ASSIGN";
    case PLUS_ASSIGN:
      return "PLUS_ASSIGN";
    case MINUS_ASSIGN:
      return "MINUS_ASSIGN";
    case TIMES_ASSIGN:
      return "TIMES_ASSIGN";
    case DIV_ASSIGN:
      return "DIV_ASSIGN";
    case LEFT_SHIFT:
      return "LEFT_SHIFT";
    case RIGHT_SHIFT:
      return "RIGHT_SHIFT";
    case GREATER_THAN_EQUAL:
      return "GREATER_THAN_EQUAL";
    case LESS_THAN_EQUAL:
      return "LESS_THAN_EQUAL";
    case INCREMENT:
      return "INCREMENT";
    case DECREMENT:
      return "DECREMENT";
    case MOD_ASSIGN:
      return "MOD_ASSIGN";
    case DOT:
      return "DOT";
    case OPEN_PARENTHESIS:
      return "OPEN_PARENTHESIS";
    case CLOSE_PARENTHESIS:
      return "CLOSE_PARENTHESIS";
    case OPEN_BRACE:
      return "OPEN_BRACE";
    case CLOSE_BRACE:
      return "CLOSE_BRACE";
    case OPEN_BRACKET:
      return "OPEN_BRACKET";
    case CLOSE_BRACKET:
      return "CLOSE_BRACKET";
    case SEMICOLON:
      return "SEMICOLON";
    case COLON:
      return "COLON";
    case COMMA:
      return "COMMA";
    case ASSIGNMENT:
      return "ASSIGNMENT";
    case BIT_OR:
      return "BIT_OR";
    case BIT_AND:
      return "BIT_AND";
    case BIT_XOR:
      return "BIT_XOR";
    case BIT_NOT:
      return "BIT_NOT";
    case NOT:
      return "NOT";
    case PLUS:
      return "PLUS";
    case MINUS:
      return "MINUS";
    case TIMES:
      return "TIMES";
    case DIV:
      return "DIV";
    case GREATER_THAN:
      return "GREATER_THAN";
    case LESS_THAN:
      return "LESS_THAN";
    case MOD:
      return "MOD";
  }
}

void printToken(Token *token, char **code) {
  char *data = tokenData(token, code);
  if (token->type == LINE_BREAK) {
    free(data);
    data = "\\n";
  }
  printf(
      ">> pos:\t%d \ttype: %s \tdata: <%s>\n",
      token->start,
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
          token.type = START_OF_KEYWORDS + i + 1;
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
        case '%': token.type = MOD_ASSIGN; continue;
      }
    }

    if (c == ':' && next_char == ':') { token.type = COLON_COLON; continue; }
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
    if (c == '%') { token.type = MOD; continue; }

    // TODO(qti3e) Use a global var for error handling.
    // Maybe call it `q_last_err`.
    printf("Error! %d %d [%c]\n", cursor, c, c);
    return NULL;
  } while (1);

  TokenArray *ret = tokens;
  ret->count = num_tokens;

  return ret;
}
