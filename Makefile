all:
	cc prompt.c ./libft/*.c ./parser/*.c -Wall -Werror -Wextra -g3 -lreadline && ./a.out
