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
HEADER 		= ./src/include

################################ Sources ####################################

SUBDIRS 	= mandatory
MAND_SRCS 	= ast/ast_split.c ast/ast.c ast/prepare_ast.c \
			builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c \
			builtins/export_utils.c builtins/export.c builtins/hashtable_utils.c \
			builtins/hashtable.c builtins/pwd.c builtins/unset.c execution/check_builtins.c execution/wait.c \
			execution/find_path.c execution/handle_logical.c execution/handle_pipes.c execution/handle_pipes_utils.c \
			execution/handle_redirects.c execution/multi_exec_cmds_utils.c execution/simple_redirect.c execution/prepare_exec2.c \
			execution/multi_exec_cmds.c execution/prepare_exec.c handle_segments/expand_dollar.c \
			handle_segments/quotes_error.c handle_segments/quotes_handler.c handle_segments/quotes_validater.c \
			handle_segments/segments_list.c handle_segments/segments_utils.c handle_segments/tilde_handler.c \
			handle_segments/wildcard_handler.c handle_segments/wildcard_utils.c parser/io_setter.c \
			parser/node_creation_utils.c parser/node_creation.c parser/parser_cmd_list_utils.c \
			parser/parser_debug_helpers.c parser/parser_tkn_list_utils.c parser/parser_utils.c parser/parser.c \
			parser/tokenizer_utils.c parser/tokenizer.c redirects/heredoc.c redirects/heredoc_utils.c redirects/heredoc_utils2.c \
			redirects/redirects.c redirects/verify_permissions.c redirects/backup_and_restore.c minishell_utils.c minishell.c \
			prompt.c cleaners.c signals/signals.c signals/signals_utils.c
		
SRCS 		= $(addprefix ./src/, $(MAND_SRCS))
# BONUS_SRCS 	= $(BONUS_SRCS:%.c=bonus/%.c)

################################ Objects ####################################

OBJS 		= $(SRCS:.c=.o)
# BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)
OBJDIR 		= ./objs

################################# Compilate #################################

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3

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