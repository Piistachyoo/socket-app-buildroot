# Add cross compilation support
CC=${CROSS_COMPILE}

# Set flags
CFLAGS = -g -Wall -Werror

all: aesdsocket
	@echo "build done!"

aesdsocket: socket.o
	$(CC) $(CFLAGS) socket.o -o aesdsocket

socket.o: socket.c
	$(CC) $(CFLAGS) -c socket.c -o socket.o

clean:
	rm -f *.o aesdsocket

check_memory: aesdsocket
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose \
	--log-file=valgrind-out.txt ./aesdsocket
