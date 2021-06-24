CC = gcc
CFLAGS = -Wall -Werror -Wextra --pedantic-errors -fstack-protector-all -Wfloat-equal -O2 -std=c17 -g
OFILES = main.o window.o shader.o texture.o cube.o camera.o
HFILES = window.h shader.h texture.h cube.h util.h camera.h
LIB = -lGL -lGLEW -lglfw -lm

main: $(OFILES)
	$(CC) -o $@ $^ $(LIB) && rm *.o

%.o: &.c $(HFILES)
	$(CC) -c -o $@ $< $(CFLAGS)