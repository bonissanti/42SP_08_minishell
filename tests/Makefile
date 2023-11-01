#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

GREEN           	= \033[1;32m
YELLOW          	= \033[1;33m
RED             	= \033[1;31m
RESET           	= \033[0m

############################# Project files ################################
SRC             	= ../src/builtins/export.c ../src/builtins/export_utils.c ../src/builtins/hashtable.c

HEADER_PROJECT  	= ../src/builtins/env.h
# HEADER_BONUS		= ../bonus/minishell_bonus.h

############################# Test files ###################################

TESTS           	= ./export/test_export.c



PROGRAM_TEST    	= $(patsubst %.c, %, $(TESTS))
# PROGRAM_TEST_BONUS 	= $(patsubst %.c, %, $(TESTS_BONUS))
HEADER_MINUNIT  	= ../minunit.h
TEST_PROGRAMS   	= $(PROGRAM_TEST)
# TEST_PROGRAMS_BONUS = $(PROGRAM_TEST_BONUS)

########################### Compile tests ###################################

all: minishell $(PROGRAM_TEST)

$(PROGRAM_TEST): $(OBJS)
	@cc $(SRC) $@.c -o $@ -L../libft -lft

########################### Compile minishell ##################################

# minishell: Call to the Makefile (minishell) in the root directory
minishell:
	$(MAKE) -C .. --no-print-directory --silent

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

m: minishell $(PROGRAM_TEST)
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

clean: clean-minishell
	@rm -f minishell minishell_bonus $(TEST_PROGRAMS) $(TEST_PROGRAMS_BONUS)
	@echo "$(YELLOW)Cleaning done!$(RESET)"

fdclean:
	@rm -f *.txt

fclean: clean fdclean

re:	fclean all fdclean

.PHONY: all clean fclean re
