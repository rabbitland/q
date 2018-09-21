#include <stdlib.h> // NULL
#include <sys/mman.h> // mmap, munmap
#include <stdio.h> // printf
#include <string.h> // memcpy
#include <stdint.h> // uintptr_t

unsigned char data[] = {
  // "Hello\n"
  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0xA
};

unsigned char code[] = {
  // To call test3()
  0x55,                           //    push   %rbp
  0x48, 0x89, 0xe5,               //    mov    %rsp,%rbp
  0xb8, 0x00, 0x00, 0x00, 0x00,   //    mov    ????,%eax
  0xff, 0xd0,                     //    callq  *%rax
  0xc9,                           //    leaveq
  0xc3,                           //    retq

  // Start of the actual program.
  0x55,                           //    push   %rbp
  0x48, 0x89, 0xe5,               //    mov    %rsp,%rbp

  0xba, 0x06, 0x00, 0x00, 0x00,   //    mov    $0x6,%edx   ; msg len
  0xb9, 0x00, 0x00, 0x00, 0x00,   //    mov    ????,%ecx   ; msg to write
  0xbb, 0x01, 0x00, 0x00, 0x00,   //    mov    $0x1,%ebx   ; file descriptor
  0xb8, 0x04, 0x00, 0x00, 0x00,   //    mov    $0x4,%eax   ; system call number (sys_write)
  0xcd, 0x80,                     //    int    $0x80       ; call kernel

  0xb8, 0x02, 0x00, 0x00, 0x00,   //    mov    $0x37,%eax
  0xeb, ~44,                      //    jmp    -44

  0xb8, 0x01, 0x00, 0x00, 0x00,   //    mov    $0x01,%eax
  0xc9,                           //    leaveq
  0xc3,                           //    retq

};

void test() {
  printf("called C function test()\n");
}

void test2() {
  printf("called C function test2()\n");
}

void test3() {
  printf("called C function test3()\n");
}

void execute () {
  char *ptr = mmap(NULL, sizeof(code), PROT_READ | PROT_WRITE | PROT_EXEC,
      MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

  int start, num;

  start = 23;
  num = (uintptr_t) &data;
  while (num > 0) {
    code[start++] = num % 256;
    num /= 256;
  }

  start = 5;
  num = (uintptr_t) &test3;
  while (num > 0) {
    code[start++] = num % 256;
    num /= 256;
  }

  memcpy(ptr, code, sizeof(code));

  int offset = 13;
  unsigned long ret = ((unsigned long (*)()) ptr + offset)();
  printf("Returned: %lx\n", ret);

  munmap(ptr, sizeof(code));
}

int main() {
  execute();
  return 0;
}
