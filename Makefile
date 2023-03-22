##
## EPITECH PROJECT, 2021
## makefile
## File description:
## makefile
##

SERVER_NAME = myteams_server
CLIENT_NAME = myteams_cli

SEVER_SRC = server/*.c
CLIENT_SRC = client/*.c

FLAGS = -Wall -Wextra -g3 -luuid -ldl

all:
	gcc -o $(SERVER_NAME) $(SEVER_SRC) $(FLAGS)
	gcc -o $(CLIENT_NAME) $(CLIENT_SRC) $(FLAGS)

clean:
	rm -f *~ | rm -f *.o

fclean: clean
	rm -f $(SERVER_NAME) | rm -f $(CLIENT_NAME)

re:	fclean all
