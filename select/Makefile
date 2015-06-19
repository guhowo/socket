# phony target
.PHONY: all
.PHONY: clean

# compile target
all: select

# compile flags
CFLAGS 	= -g -Wall
CC 	= gcc

# compile
select: select.o
	$(CC) $(CFLAGS) -o select select.o

clean:
	-rm -f *.o  select
