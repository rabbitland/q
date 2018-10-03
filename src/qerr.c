#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "qerr.h"

// Print the last error and exit the process with a non-zero exit code.
void qerror() {
  if (last_error.code == NO_ERROR) return;

  if (last_error.code == UNEXCPECTED_CHAR) {
    char ch = last_error.data.unexcpected_char.character;
    char *fmt_str;
    if (isprint(ch)) {
      fmt_str = "Unexcpected character \"%c\" found at position %d.\n";
    } else {
      fmt_str = "Unexcpected character 0x%02hhx found at position %d.\n";
    }
    printf(fmt_str, ch, last_error.data.unexcpected_char.pos);
  }

  if (last_error.code == UNEXCPECTED_TOKEN) {
    struct UNEXCPECTED_TOKEN data = last_error.data.unexcpected_token;
    printf("Excpected %s at %d found %s.\n", TOKEN_STRINGS[data.excpected],
        data.pos, TOKEN_STRINGS[data.actual]);
  }

  exit(-1);
}

void clear_error() {
  last_error.code = NO_ERROR;
}
