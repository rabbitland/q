#ifndef __Q_ERROR__
#define __Q_ERROR__

enum ERROR_CODES {
  NO_ERROR,
  // It happens when there is a character in the source code
  // that is not recognized by the tokenizer.
  UNEXCPECTED_CHAR,
  // Unexcpected token.
  UNEXCPECTED_TOKEN
} qerrno;

struct UNEXCPECTED_CHAR {
  int pos;
  char character;
};

struct UNEXCPECTED_TOKEN {
  int pos;
  int actual;
  int excpected;
};

struct Error {
  enum ERROR_CODES code;
  union {
    struct UNEXCPECTED_CHAR unexcpected_char;
    struct UNEXCPECTED_TOKEN unexcpected_token;
  } data;
} typedef Error;

Error last_error;
void qerror();
void clear_error();

#endif
