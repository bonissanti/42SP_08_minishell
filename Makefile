#----------------------- Makefile for minishell ---------------------------# 
################################ Colors ####################################    

RED      	= \033[1;31m
GREEN    	= \033[1;32m
YELLOW   	= \033[1;33m
BLUE     	= \033[1;34m
RESET    	= \033[0m

################################ Project ####################################

NAME 		= minishell
# NAME_BONUS = n/a
LIBFT 		= ./libft
MINISHELL 	= ./
HEADER 		= ./mandatory/

################################ Sources ####################################

SUBDIRS 	= mandatory
MAND_SRCS 	= 	builtins/export.c builtins/export_utils.c builtins/hashtable.c \
				builtins/exit.c builtins/env.c builtins/cd.c builtins/pwd.c \
				builtins/main.c builtins/echo.c builtins/unset.c \
				handle_segments/handle_quotes.c handle_segments/segments_utils.c \
			
		
SRCS 		= $(addprefix ./src/, $(MAND_SRCS))
# BONUS_SRCS 	= $(BONUS_SRCS:%.c=bonus/%.c)

################################ Objects ####################################

OBJS 		= $(SRCS:.c=.o)
# BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)
OBJDIR 		= ./objs

################################# Compilate #################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

LIBFT_MAKE = $(MAKE) -C $(LIBFT) --no-print-directory
LIBFT_LIB = $(LIBFT)/libft.a

################################## Rules ####################################

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS:%=$(OBJDIR)/%)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS:%=$(OBJDIR)/%) -I $(HEADER) -L $(LIBFT) -lft -lreadline
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(LIBFT_LIB):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(LIBFT_MAKE)
	@echo "$(GREEN)Libft compiled$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling: $(RESET)$<..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

################################## Norm #####################################

norm:
	@echo "$(YELLOW)Norminette:$(RESET)"
	@norminette $(SRCS) $(HEADER)
	@echo "$(GREEN)Norminette done$(RESET)"

################################## Clean ####################################

clean:
	@$(LIBFT_MAKE) clean
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)Objects deleted$(RESET)"

fclean: clean
	@$(LIBFT_MAKE) fclean
	@rm -rf $(NAME)
	@echo "$(YELLOW)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re norm