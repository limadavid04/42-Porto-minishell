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
CFLAGS = -Wall -Wextra -Werror -lreadline

all: main

main: main.c
	@$(CC) $(CFLAGS) -o Minishell main.c
	@echo -n "[$(CYAN)Compiling$(RESET)]"
	@sleep 1
	@echo -n " ."
	@sleep 1
	@echo -n " ."
	@sleep 1
	@echo " ."
	@echo "[$(GREEN)Done!$(RESET)]"

clean:
	@$(RM) $(OBJS)
	@echo -n "[$(CYAN)Cleaning$(RESET)]"
	@sleep 1
	@echo -n " ."
	@sleep 1
	@echo -n " ."
	@sleep 1
	@echo " ."
	@echo "[$(GREEN)Done!$(RESET)]"

fclean: clean	
	@$(RM) $(MAKE)
	@echo -n "[$(CYAN)F Cleaning$(RESET)]"
	@sleep 1
	@echo -n " ."
	@sleep 1
	@echo -n " ."
	@sleep 1
	@echo " ."
	@echo "[$(GREEN)Done!$(RESET)]"

re: fclean all