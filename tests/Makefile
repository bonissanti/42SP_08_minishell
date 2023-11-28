#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

GREEN           	= \033[1;32m
YELLOW          	= \033[1;33m
RED             	= \033[1;31m
RESET           	= \033[0m

############################# Project files ################################
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
					./export/export_basic_cmds.c
					


PROGRAM_TEST    	= $(patsubst %.c, %, $(TESTS))
# PROGRAM_TEST_BONUS 	= $(patsubst %.c, %, $(TESTS_BONUS))
HEADER_MINUNIT  	= ../minunit.h
TEST_PROGRAMS   	= $(PROGRAM_TEST)
# TEST_PROGRAMS_BONUS = $(PROGRAM_TEST_BONUS)

########################### Compile tests ###################################

all: minishell $(PROGRAM_TEST)

$(PROGRAM_TEST): $(OBJS)
	@cc $(SRC) $@.c -o $@ -L../libft -lft -lreadline

########################### Compile minishell ##################################

# minishell: Call to the Makefile (minishell) in the root directory
minishell:
	$(MAKE) -C .. 

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
	$(MAKE) -C .. fclean --no-print-directory --silent

clean: clean-minishell fdclean
	@rm -f minishell minishell_bonus $(TEST_PROGRAMS) $(TEST_PROGRAMS_BONUS)
	@echo "$(YELLOW)Cleaning done!$(RESET)"

fdclean:
	@rm -f *.txt

fclean: clean fdclean

re:	fclean all fdclean

.PHONY: all clean fclean re
