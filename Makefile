CFLAGS = -Wall -Wextra -O2
all : server client
server : server.c conf.h
	gcc $(CFLAGS) server.c -o server
client : client.c conf.h
	gcc $(CFLAGS) client.c -o client

