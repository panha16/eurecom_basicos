CC = gcc
CFLAGS = -Wunused-variable
TARGETS = myfs 

.PHONY: all clean

all: $(TARGETS)
# All binaries will be stored under src/bin/
myfs: myfs.c
	$(CC) $(CFLAGS) -o bin/$@ definitions.c $@.c
clean:
	rm -f bin/$(TARGETS)