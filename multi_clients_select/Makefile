# phony target
.PHONY: all
.PHONY: clean

# compile target
all: server client

# compile flags
CFLAGS 	= -g -Wall
CC 	= gcc

# compile
server: server.o
	$(CC) $(CFLAGS) -o server server.o

client: client.o
	$(CC) $(CFLAGS) -o client client.o

server.o: multi_clients_select.h
client.o: multi_clients_select.h

clean:
	-rm -f *.o  server client
