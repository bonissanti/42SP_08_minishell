#include "../minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/builtins/env.h"


/**
 * Color structure ANSI
 * -----------------
 * ANSI colors are escape sequences that are used to apply color to the output.
 * The escape sequences are composed of the following parts:
 * 
 * \033: Escape character
 * [1;31m: Color code, where 1 is bold and 31 is red text and 'm' is the end of the
 * color sequence. For use regular text, change 1 to 0, and for use italic text,
 * change 1 to 3.
 * 
 * Is possible to use text with background color, for this, change the '1' to '4'
 * and the color code to the desired color.
 *  
 * @\033[1;31m: Red bold text
 * @\033[1;32m: Green bold text
 * @\033[1;33m: Yellow bold text
 * @\033[1;34m: Blue bold text
 * @\033[1;37m: White bold text
 * @\033[0;31m: Red bold text
 * @\033[0m: Reset
 * 
 * @return: Returns nothing.
 *
 */


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

void compare_files(char *filename1, char *filename2)
{
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");
    char line1[10000];
    char line2[10000];
    int number_line = 1;
    t_bool is_equal = true;

    if (file1 == NULL || file2 == NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }
    while (fgets(line1, 10000, file1) != NULL && fgets(line2, 10000, file2) != NULL)
    {
        if (strcmp(line1, line2) != 0)
        {
            is_equal = false;
            printf("\033[1;31;41mFiles are not equal at line %d\033[0m\n", number_line);
            printf("\033[0;31mFile 1: %s\n", line1);
            printf("\033[0;31mFile 2: %s\n", line2);
            exit(1);
        }
        number_line++;
    }
    if (is_equal == true)
        printf("\033[1;32mFiles are equal\n");

}

MU_TEST(test_tokenization)
{
	char *command = "<< qwerty > ./output | < ./infile wc -l > ./output && echo \"test\" || (sort ./test)";
    // char *result = tokenization(command);

    send_command_and_write_to_file("export", "outfile_result.txt");

    compare_files("outfile_result.txt", "outfile_shell.txt");

    // char *minishell_output = read_line("outfile_result.txt");
    // char *bash_output = read_line("outfile_shell.txt");

    // mu_assert_string_eq(minishell_output, bash_output);
    // free(minishell_output);
    // free(bash_output);
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