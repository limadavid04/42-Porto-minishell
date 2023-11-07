NAME = lexer
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = lexer.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
		$(MAKE) --no-print-director -C ./libft
	
$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) libft/libft.a -o $(NAME)
		echo Makefile done!

clean:
		$(MAKE) clean --no-print-director -C ./libft
		$(RM) $(OBJS)
		echo clean done!

fclean: clean
		$(MAKE) fclean --no-print-director -C ./libft
		$(RM) libft.a
		$(RM) $(MAKE)
		echo fclean done!

re: fclean all