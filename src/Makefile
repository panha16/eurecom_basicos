CC = gcc
CFLAGS = -Wall
TARGETS = myfs 

.PHONY: all clean

all: $(TARGETS)
# All binaries will be stored under src/bin/
myfs: myfs.c
	$(CC) $(CFLAGS) -o bin/$@ read.c create.c ls.c remove.c size.c write.c definitions.c $@.c
clean:
	rm -f bin/$(TARGETS)