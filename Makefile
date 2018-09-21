BINDIR  = bin
CFLAGS  = -Wall -Wextra --std=gnu99 -fpie -Wno-format
LDFLAGS = -lrt
CC = gcc
TARGET  = $(BINDIR)/q

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(BINDIR)
	$(CC) $(CFLAGS) src/main.c -o $(TARGET) $(LDFLAGS)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf ./$(BINDIR)
