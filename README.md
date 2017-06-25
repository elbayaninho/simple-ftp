# simple-ftp
Simple FTP with socket in C programming
Baimi Badjoua <elbayaninho@outlook.fr> and
Bio Nikki Bruno <brunobionikki@yahoo.fr>
===================================================
MYFTPD and MYFTP

CONTENTS:
	files
    instructions
    Unknown problems

1- Files
	client/client.c
		code-source for client

	client/client.h
		header for client

	myftp
		executable for client

	common/commands.txt
		available commands listing

	common/common.h
		commonly header for client and server

	common/functions.c
		for external functions used in the project

	common/functions.h
		header for our personal functions

	common/temp.txt
		file generated for commands like ls, cd... in the server

	common/temps.txt
		file generated for commands like get, put... in the server

	server/server.c
		code-source for server

	server/server.h
		header for server

	server/myftpd
		executable for server

	Makefile
		compilation script

	readme.md
		general project overview

2- Instructions

    Compiling the programs.

        Run the command 'make all'.


    Using the myftp : client.

        Usage:
            ./myftp <server name or IP>

    Using the myftpd : server.

        Usage:
            ./myftpd <hostname or IP>

    General instruction:
    	In Linux you must execute client and server as root
    	for full access.

3- Unknown problems:

	We have a problem with looping client to connect with the 
	server until post 'bye' like command. After three commands
	in the server the connection will closed.

