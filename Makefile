NAME = pipex

BONUS = pipex_bonus

CFLAGS = -Wall -Wextra -Werror

BONUSFLAGS = -D BONUS=1

CC = gcc
#PUT FILES HERE
SRCS_FILE = main.c	tool.c	run_command.c	bonus.c

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

LIBFLAGS = -L ./libft -lft

#PUT HEADERS HERE
HEADER_FILE = pipex.h

HEADER_PATH = includes/

HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))

all : $(NAME)
	echo "Compile OK"

$(NAME) : $(HEADER) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -I $(HEADER_PATH) -c srcs/main.c -o srcs/main.o
	$(CC) $(CFLAGS) -I $(HEADER_PATH) $(OBJS) $(LIBFLAGS) -o $(NAME)

$(BONUS) : $(HEADER) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(BONUSFLAGS) -I $(HEADER_PATH) -c srcs/main.c -o srcs/main.o
	$(CC) $(CFLAGS) -I $(HEADER_PATH) $(OBJS) $(LIBFLAGS) -o $(BONUS)

$(LIBFT) : 
	$(MAKE) -C ./libft/

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(HEADER_PATH) -c $< -o $@

bonus : $(BONUS)
	echo "Compile Bonus OK"

clean : 
	rm -rf $(OBJS)
	$(MAKE) clean -C ./libft/
	echo "clean OK"

fclean :
	rm -rf $(OBJS) $(NAME) $(BONUS)
	$(MAKE) fclean -C ./libft/
	echo "fclean OK"

re : fclean all

.PHONY: all clean fclean re bonus

.SILENT : 
