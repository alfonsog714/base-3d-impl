CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -g
LDFLAGS := -lSDL2

SRCS := \
src/main.c

TARGET := renderer

all: build

build: $(TARGET)

$(TARGET): display.o
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) display.o $(LDFLAGS)

display.o:
	$(CC) $(CFLAGS) -c src/display.c

run: $(TARGET)
	./renderer

clean:
	rm renderer *.o

.PHONY: all clean run
