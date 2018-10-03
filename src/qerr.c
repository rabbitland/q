#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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

  // TODO(qti3e) Handle other errors.
  printf("Error!\n");
  exit(-1);
}

void clear_error() {
  last_error.code = NO_ERROR;
}
