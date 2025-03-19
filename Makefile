CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -g
LDFLAGS := -lSDL2

SRCS := \
src/main.c \
src/display.c \
src/vector.c

TARGET := renderer

all: build

build: $(TARGET)

$(TARGET): 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run: $(TARGET)
	./renderer

clean:
	rm renderer

.PHONY: all clean run
