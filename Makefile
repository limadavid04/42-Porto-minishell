.SILENT:


#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COLORS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory
FILES = main lexer/lexer lexer/lexer_utils lexer/lexer_utils2 lexer/lexer_utils1 utils/quotes
OBJS = $(addsuffix .o, $(FILES))
NAME = minishell
LIBFT = ./libft/libft.a
RM = rm -f

all: $(NAME)

$(LIBFT):
	@echo -n "[$(CYAN)Compiling Libft$(RESET)]"
	@$(MAKE)  --no-print-director -C ./libft
	@echo "[$(GREEN)Libft Done!$(RESET)]"

$(NAME): $(OBJS) $(LIBFT)
	@echo -n "[$(CYAN)Compiling Minishell$(RESET)]"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "[$(GREEN)Minishell Done!$(RESET)]"

clean:
	@echo -n "[$(CYAN)Cleaning$(RESET)]"
	@$(RM) $(OBJS)
	@$(MAKE) clean --no-print-director -C ./libft
	@echo "[$(GREEN)Done!$(RESET)]"

fclean: clean
	@echo -n "[$(CYAN)F Cleaning$(RESET)]"
	@$(MAKE) fclean --no-print-director -C ./libft
	@$(RM) libft.a
	@$(RM) $(MAKE)
	@echo "[$(GREEN)Done!$(RESET)]"

re: fclean all

