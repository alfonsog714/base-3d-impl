CC = gcc

build:
	$(CC) -Wall -std=c99 ./src/*.c -o renderer

run:
	./renderer

clean:
	rm renderer
