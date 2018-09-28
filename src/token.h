#ifndef __Q_TOKEN__
#define __Q_TOKEN__

enum TokenType {
  LINE_BREAK,
  // Many bytes
  NUMERIC_LITERAL,
  STRING_LITERAL,
  COMMENT,
  IDENTIFIER,
  START_OF_KEYWORDS,
  IF_KEYWORD,
  WHILE_KEYWORD,
  FOR_KEYWORD,
  BREAK_KEYWORD,
  CONTINUE_KEYWORD,
  RETURN_KEYWORD,
  SWITCH_KEYWORD,
  CASE_KEYWORD,
  USE_KEYWORD,
  VAR_KEYWORD,
  PRINT_KEYWORD,
  INT_KEYWORD,
  VOID_KEYWORD,
  STRING_KEYWORD,
  NULL_KEYWORD,
  END_OF_KEYWORDS,
  // Two byte
  COLON_COLON, // ::
  DOT_DOT, // ..
  EQUALITY, // ==
  INEQUALITY, // !=
  LOGICAL_OR, // ||
  LOGICAL_AND, // &&
  BIT_OR_ASSIGN, // |=
  BIT_XOR_ASSIGN, // ^=
  BIT_NOT_ASSIGN, // ~=
  AND_ASSIGN, // &=
  PLUS_ASSIGN, // +=
  MINUS_ASSIGN, // -=
  TIMES_ASSIGN, // *=
  DIV_ASSIGN, // /=
  LEFT_SHIFT, // <<
  RIGHT_SHIFT, // >>
  GREATER_THAN_EQUAL, // >=
  LESS_THAN_EQUAL, // <=
  INCREMENT, // ++
  DECREMENT, // --
  MOD_ASSIGN, // %=
  // One byte
  DOT, // .
  OPEN_PARENTHESIS, // (
  CLOSE_PARENTHESIS, // )
  OPEN_BRACE, // {
  CLOSE_BRACE, // }
  OPEN_BRACKET, // [
  CLOSE_BRACKET, // ]
  SEMICOLON, // ;
  COLON, // :
  COMMA, // ,
  ASSIGNMENT, // =
  BIT_OR, // |
  BIT_AND, // &
  BIT_XOR, // ^
  BIT_NOT, // ~
  NOT, // !
  PLUS, // +
  MINUS, // -
  TIMES, // *
  DIV, // /
  GREATER_THAN, // >
  LESS_THAN, // <
  MOD, // %
};

struct Token {
  enum TokenType type;
  int start;
  int len;
} typedef Token; 

struct TokenArray {
  size_t count;
  Token tokens[];
} typedef TokenArray;

char *tokenData(Token *token, char **code);
char *tokenName(Token *token);
void printToken(Token *token, char **code);
void freeTokenArray(TokenArray *t);
TokenArray *tokenize(char *code, int skip_comments);

#endif
