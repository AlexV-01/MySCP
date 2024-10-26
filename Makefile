CC = gcc
CFLAGS = -Wall -g -fsanitize=address,undefined

all: myscp
	make clean

myscp: myscp.o client.o server.o
	$(CC) $(CFLAGS) -o myscp myscp.o client.o server.o

myscp.o: myscp.c myscp.h
	$(CC) $(CFLAGS) -c myscp.c

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c

server.o: server.c server.h
	$(CC) $(CFLAGS) -c server.c

clean:
	rm -f *.o
