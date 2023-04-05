P=main
OBJECTS=memory.o chunk.o debug.o value.o vm.o
CFLAGS= -g -Wall -O0
LDLIBS=
CC=c99

$(P): $(OBJECTS)
