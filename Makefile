BINDIR  = bin
CFLAGS  = -Wall -Wextra --std=gnu99 -fpie -Wno-format
LDFLAGS = -lrt
CC = gcc
TARGET  = $(BINDIR)/q
SOURCES=$(wildcard src/*.c )

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(BINDIR) $(SOURCES)
	$(CC) $(CFLAGS) src/main.c -o $(TARGET) $(LDFLAGS)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf ./$(BINDIR)
