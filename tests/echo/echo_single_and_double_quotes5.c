#include "../minunit.h"


/**
 * Function: Send_command_and_write_to_file
 * -----------------
 * This function is used to pass a command to the minishell and write the output
 * to a file. The first argument is the command to be passed, and the second
 * argument is the name of the file to be written.
 * 
 * To process the command, the function popen is used. It opens a process by
 * creating a pipe, forking, dupping the pipe into stdin/stdout, and executing
 * the given command. The function returns a pointer to the file.
 *  
 * @param: command: The command to be passed to the minishell.
 * @param: filename: The name of the file to be written.
 * 
 * @var: fp: The pointer to the file.
 * @var: outfile: The pointer to the file.
 * @var: buffer: The buffer to store the output of the command.
 * 
 * @return: Returns a pointer to the file.
 *
 */

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

/**
 * Function: Read_line
 * -----------------
 * This function is used to read a line from a file and return it as a string.
 * 
 * @param: filename: The name of the file to be read.
 * 
 * @var: file: The pointer to the file.
 * 
 * @return: Returns a pointer to the string.
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

/**
 * Function: Compare_files
 * -----------------
 * This function is used compare two strings generated by the function
 * read_line. If the strings are not equal, the function will print the
 * line where the strings are different and exit the program. If the strings
 * are equal, the function will print that the files are equal.
 * 
 * Thus, we will be able to check if the output of the minishell is equal to
 * the output of the bash.
 * 
 * @param: filename1: The name of the first file to be read.
 * @param: filename2: The name of the second file to be read.
 * 
 * @var: file1: Pointer to the first file, used to read the first file.
 * @var: file2: Pointer to the second file, used to read the second file.
 * @var: line1: Pointer to the string of the first file, used to store the
 *             string of the first file.
 * @var: line2: Pointer to the string of the second file, used to store the
 *            string of the second file.
 * @var: number_line: The number of the line where the strings are different.
 * @var: is_equal: Boolean variable used to check if the strings are equal.
 * 
 * @return: Returns nothing.
 *
 */

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
        printf(RED"Failed to open file\n"RESET);
        exit(1);
    }
    while (fgets(line1, 10000, file1) != NULL && fgets(line2, 10000, file2) != NULL)
    {
        if (strcmp(line1, line2) != 0)
        {
            is_equal = false;
            printf(RED"Files are not equal at line %d\n" RESET, number_line);
            printf("File 1: %s", line1);
            printf("File 2: %s\n", line2);
            exit(1);
        }
        number_line++;
    }
    if (is_equal == true)
        printf(GREEN"Files are equal\n" RESET);

}

/**
 * Function: Test_...
 * -----------------
 * This function is used by the minunit library to run a test. It is used to
 * test the command or some part of the code.
 * 
 * @param: void: The function does not receive any arguments.
 * @function: system: The system function is used to run a command in the shell.
 * 
 * @return: Returns nothing.
 *
 */

MU_TEST(echo_2arg_to_file)
{
	pid_t pid;

    pid = fork();
	system("echo '\"$USER'\"'\" > ./txts/echo_single_and_double_quotes5.txt");

    if (pid == 0)
        execlp("/nfs/homes/brunrodr/09.MINISHELL/42SP_08_minishell/minishell", "minishell", NULL);
    else if (pid > 0)
    {
        sleep(1);
        kill(pid, SIGINT);
    }

    send_command_and_write_to_file("echo '\"$USER'\"'\"", "./txts/echo_single_and_double_quotes5_minishell.txt");
    compare_files("./txts/echo_single_and_double_quotes5_minishell.txt", "./txts/echo_single_and_double_quotes5_bash.txt");
}


MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(echo_2arg_to_file);
}

int main(void)
{
    printf("\n------------------- TEST ECHO n°3 -------------------\n");
    MU_RUN_SUITE(test_suite);
    // MU_REPORT();
    return (0);
}
