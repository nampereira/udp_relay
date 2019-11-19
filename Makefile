CC=gcc
CFLAGS=-I.
DEPS = simple_sock.h simple_sock.c
OBJ = simple_sock.o udp_relay.o 
ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    LDFLAGS = -lws2_32.lib
endif

%.o: %.c $(DEPS)
	$(CC) -c $(LDFLAGS) -o $@ $< $(CFLAGS) 

udprelay: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(CFLAGS)
