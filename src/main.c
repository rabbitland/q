#include <stdlib.h>
#include <stdio.h>
#include "token.h"

int main() {
  char* code = "xsa if x |= 3;\n\
                // test \n\
                var = 32 + x * 4;\n\
                DA = 'Hello World';\n\
                c = 's\\' s'";
  void* tokens = tokenize(code);

  printf("---\n");
  for (int i = 0; ; i += sizeof(Token)) {
    char *x = tokens + i;
    if (x[0] == 0x00) {
      break;
    }
    printToken(tokens + i, code);
  }

  free(tokens);

  return 0;
}
