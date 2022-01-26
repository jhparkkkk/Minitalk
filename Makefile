CC			= 	cc  

RM 			= 	rm -f

CFLAGS		=	-Wall -Wextra -Werror

NAME 		= 	minitalk
BONUS		=	minitalk_bonus
SRC_CLIENT 	=	client.c
SRC_SERVER 	= 	server.c			
OBJ_CLIENT 	= 	$(SRC_CLIENT:.c=.o)
OBJ_SERVER 	= 	$(SRC_SERVER:.c=.o)

BONUS_SRC_CLIENT 	=	client_bonus.c
BONUS_SRC_SERVER 	=	server_bonus.c			
BONUS_OBJ_CLIENT 	=	$(BONUS_SRC_CLIENT:.c=.o)
BONUS_OBJ_SERVER 	=	$(BONUS_SRC_SERVER:.c=.o)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@  

all:		$(NAME) 

client:		$(OBJ_CLIENT)
			$(CC) $(CFLAGS) $(OBJ_CLIENT) ${OUTPUT_OPTION}

server :	$(OBJ_SERVER)
			$(CC) $(CFLAGS) $(OBJ_SERVER) ${OUTPUT_OPTION}

b_client :	$(BONUS_OBJ_CLIENT)
			$(CC) $(CFLAGS) $(BONUS_OBJ_CLIENT) -o client_bonus

b_server :	$(BONUS_OBJ_SERVER)
			$(CC) $(CFLAGS) $(BONUS_OBJ_SERVER) -o server_bonus

$(NAME):	server client

$(BONUS):	client_bonus server_bonus

clean:
			$(RM) $(NAME) $(BONUS) $(OBJ_CLIENT) $(OBJ_SERVER) $(BONUS_OBJ_CLIENT) $(BONUS_OBJ_SERVER)

fclean:		clean
			$(RM) server client server_bonus client_bonus

re:			fclean all

bonus:		$(BONUS)

.PHONY:		all clean fclean re 

