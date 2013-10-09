# Installing watchmen

CC=gcc

FLAGS=-std=c99

NAME=watchmen.c

GLOBAL=/usr/bin/watchmen

LOCAL=./bin/watchmen

install:
	$(CC) -o $(GLOBAL) $(NAME) $(FLAGS)

install_local:	
	$(CC) -o $(LOCAL) $(NAME) $(FLAGS)

clean:
	rm -rf $(LOCAL) $(GLOBAL)
