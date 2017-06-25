# Authors: BAIMI BADJOUA & BIO NIKKI BRUNO
# University: IFRI_UAC
# Copyright: MIT Licence X11
# Date: 2017/06/19
# Comment: Makefile for myftp

CFLAGS = -Wall -g
CC = gcc
LDFLAGS = 
EXEC = server/myftpd client/myftp # server: myftpd and client: myftp

all: $(EXEC)

server/myftpd:	server.o functions.o
	$(CC) -o server/myftpd server.o functions.o $(CFLAGS)

server.o:	server/server.c common/functions.c server/server.h  common/common.h common/functions.h
	$(CC) -c server/server.c common/functions.c

client/myftp:	client.o functions.o
	$(CC) -o client/myftp client.o functions.o $(CFLAGS)

client.o:	client/client.c common/functions.c client/client.h  common/common.h common/functions.h
	$(CC) -c client/client.c common/functions.c

functions.o:	common/functions.c  common/common.h common/functions.h
	$(CC) -c common/functions.c

clean:
	rm -rf *.o 

mrproper:	clean
	rm -rf $(EXEC)
