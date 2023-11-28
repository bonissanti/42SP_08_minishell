#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

RED      	= \033[1;31m
GREEN    	= \033[1;32m
YELLOW   	= \033[1;33m
BLUE     	= \033[1;34m
RESET    	= \033[0m

############################# Project files ################################

# NAME 				= tests

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

TESTS           	= ./echo/echo_1arg_to_file.c \
					./echo/echo_2arg_to_file.c \
					./echo/echo_expand_var.c \
					./echo/echo_expand_var_single_quotes.c \
					./export/export_var.c
					
PROGRAM_TEST    	= $(patsubst %.c, %, $(TESTS))
HEADER_MINUNIT  	= ../minunit.h
TEST_PROGRAMS   	= $(PROGRAM_TEST)

OBJDIR          = ./objs

############################# Compilation ###################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 

########################### Compile tests ###################################

all: m $(PROGRAM_TEST)

$(PROGRAM_TEST): $(OBJS)
	@cc $(SRC) $@.c -o $@ -L../libft -lft -lreadline

########################### Compile minishell ##################################

m:
	@$(MAKE) -C .. --no-print-directory --silent

############################## Execution ####################################

# Test: Run the tests compiled
test: $(TEST_PROGRAMS)
	@for program in $(TEST_PROGRAMS); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done

run: minishell $(PROGRAM_TEST)
	@for program in $(PROGRAM_TEST); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done

############################## Valgrind #####################################

# Leak: Run the tests compiled with valgrind with complete leak check
leak: test
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes -s -q ./${PROGRAM_TEST}

############################## Clean ########################################

clean-minishell:
	@$(MAKE) -C .. fclean --no-print-directory --silent

clean: clean-minishell tclean
	@rm -f minishell minishell_bonus $(TEST_PROGRAMS) $(TEST_PROGRAMS_BONUS)
	@echo "$(YELLOW)Cleaning done!$(RESET)"

tclean:
	@rm -rf ./txts
	@echo "$(YELLOW)Files .txt deleted!$(RESET)"

fclean: clean tclean 
	@echo "$(YELLOW)Full cleaning done!$(RESET)"
	@rm -rf $(OBJDIR)

re:	fclean all tclean

.PHONY: all clean fclean re
