CC = gcc
CFLAGS = -g -c -fsanitize=address,undefined

EXEC = myscp

SRC = myscp.c client.c server.c

OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf testfile *.o *.a