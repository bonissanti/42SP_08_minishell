#include "env.h"

int ft_count_args(char **args)
{
    int count;

    count = 0;
    while (args[count] != NULL)
        count++;
    return (count);
}

void ft_exit(char **args)
{
    long int exit_code;
    int argc;

    exit_code = 0;
    argc = ft_count_args(args);
    if (argc == 1)
        exit (0);
    else if (argc == 2)
    {
        if (!ft_isdigit(args[1][0]))
            ft_putstr_fd("exit: numeric argument required\n", 2);
        exit_code = ft_atol(args[1]);
        exit(exit_code);
    }
    else
        ft_putstr_fd("exit: too many arguments\n", 2);
}