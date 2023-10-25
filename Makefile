all:
	cc minishell.c prompt.c ./libft/*.c -Wall -Werror -Wextra -g3 -lreadline && ./a.out
