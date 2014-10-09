# Makefile for sulliticker
CC=gcc
CFLAGS=-c -W -Wall -ansi -pedantic
LDFLAGS=
EXECUTABLE=server
OBJ=server.o arduino-serial-lib.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXECUTABLE)

server.o: server.c
	$(CC) $(CFLAGS) server.c

arduino-serial-lib.o: arduino-serial-lib.c
	$(CC) -c arduino-serial-lib.c

clean:
	rm -rf *.o $(EXECUTABLE)
