#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

RED      	= \033[1;31m
GREEN    	= \033[1;32m
YELLOW   	= \033[1;33m
BLUE     	= \033[1;34m
RESET    	= \033[0m

############################# Project files ################################

NAME 				= minunit

SRC             	= ../src/ast/ast.c \
					../src/ast/ast_split.c \
					../src/builtins/export.c \
					../src/builtins/export_utils.c \
					../src/builtins/hashtable.c \
					../src/builtins/exit.c \
					../src/builtins/env.c \
					../src/builtins/cd.c \
					../src/builtins/pwd.c \
					../src/builtins/echo.c \
					../src/builtins/unset.c \
					../src/handle_segments/quotes_handler.c \
					../src/handle_segments/segments_utils.c \
					../src/handle_segments/expand_dollar.c \
					../src/handle_segments/quotes_validater.c \
					../src/handle_segments/quotes_error.c \
					../src/handle_segments/tilde_handler.c \
					../src/handle_segments/wildcard_handler.c \
					../src/handle_segments/wildcard_utils.c \
					../src/execution/find_path.c \
					../src/execution/prepare_exec.c \
					../src/execution/exec_cmds.c \
					../src/execution/check_builtins.c \
					../src/redirects/check_redirects.c \
					../src/redirects/redirects.c \
					../src/redirects/heredoc.c \
					../src/redirects/verify_permissions.c \
					../src/minishell_utils.c \

############################# Test files ###################################

TESTS_ECHO         	= ./echo/echo_1arg_to_file.c
TESTS_ECHO_OBJ 		= $(patsubst %.c, %.o, $(TESTS_ECHO))


OBJDIR          	= ./objs

########################### Compile minishell ##################################

m:
	@$(MAKE) -C .. --no-print-directory --silent

############################## Compile tests ##################################

all: $(NAME)

$(NAME): $(OBJDIR) $(TESTS_ECHO_OBJ:%=$(OBJDIR)/%)
	@$(CC) $(CFLAGS) -o $(NAME) $(TESTS_ECHO_OBJ:%=$(OBJDIR)/%) $(SRC) -L .. -lft -lreadline
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

run: $(NAME)
	@./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)$(NAME) objects deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all
