#include "../minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../bonus/pipex_bonus.h"

/**
 * Function: run_command
 * -----------------
 * This function is used to run a command and return the result. It is used to
 * run shell commands and my pipex program.
 * 
 * @param: *command: the command to run.
 * @param: *fp: pointer to the file.
 * @param: popen: opens the file.
 * @param: fgets: reads the file, aka the shell command or pipex parameters.
 * @param: pclose: closes the file.
 * @param: *result: pointer to the result.
 *
 * @return: Returns the result, which is the output of the shell command or pipex.
 *
 */

char    *run_command(char *command)
{
    FILE *fp;

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    char *output = malloc(sizeof(char) * 1000);
    fgets(output, 1000, fp);

    pclose(fp);

    return (output);
}

char    *read_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }
    char    *content = malloc(sizeof(char) * 1000);
    fgets(content, 1000, file);
    fclose(file);
    return (content);
}

MU_TEST(test_bonus_grep_sort_count)
{
	run_command("../pipex_bonus ../infile \"ls -l\" \"grep .c\" \"sort\" ../outfile_result");
    run_command("< ../infile ls -l | grep \".c\" | sort > ../outfile_expected");

    char *pipex_output = read_file("../outfile_result");
    char *shell_output = read_file("../outfile_expected");

    mu_assert_string_eq(pipex_output, shell_output);

    free(pipex_output);
    free(shell_output);
}



MU_TEST_SUITE(test_suite)
{
	MU_RUN_TEST(test_bonus_grep_sort_count);
}

int main(void)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}