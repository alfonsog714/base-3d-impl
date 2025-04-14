CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=gnu11 -g
LDFLAGS := -lSDL2
LDFLAGS += -lm

SRCS := \
src/main.c \
src/display.c \
src/vector.c \
src/mesh.c \
src/triangle.c \
src/array.c \
src/matrix.c \
src/light.c

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
