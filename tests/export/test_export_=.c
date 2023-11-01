#include "../minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/builtins/env.h"

FILE *send_command_and_write_to_file(char *command, char *filename)
{
    FILE *fp;
    FILE *outfile;

    char buffer[1024];

    fp = popen(command, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    outfile = fopen(filename, "w");
    if (outfile == NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        fputs(buffer, outfile);
    pclose(fp);
    fclose(outfile);
    return (outfile);
}

char *read_line(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }
    char *content = malloc(sizeof(char) * 1024);
    fgets(content, 1024, file);
    fclose(file);
    return (content);
}

MU_TEST(test_export)
{
	system("export VAR= && export > outfile_shell2.txt");
    system("/nfs/homes/brunrodr/09.MINISHELL/42SP_08_minishell/minishell");

    send_command_and_write_to_file("export", "outfile_result2.txt");

    char *minishell_output = read_line("outfile_result2.txt");
    char *bash_output = read_line("outfile_shell2.txt");

	mu_assert_string_eq(minishell_output, bash_output);
    // mu_assert_string_eq(minishell_output, bash_output);
    free(minishell_output);
    free(bash_output);
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_export);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (0);
}

// echo aaaa > file | tr a C


// Tokenização - split de todas a palavras e operadores ("", '', |, >, >>, >, <, <<);

// Analise Lexica - transformar os tokens em WORD, PIPE, GREATER, DGREATER,) 

// // enum {
// //     AND 5
// //     PIPE 4
// // }

// Analise Sintática - word word pipe word dgreater greater 

// Separar os tokens em Commandos - Lista linkadas split pelos PIPES (stdin operação stdout)

// Node {

//     __REDIRECT

//         arg1_execve
//         arg2_execve;

//         stdin
//         stdout
// }

// Pipex