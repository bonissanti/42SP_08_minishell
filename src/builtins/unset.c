#include <stdlib.h>
#include <stdio.h>

int ft_unset(char **args)
{
    int i;

    i = 0;
    if (args[1] == NULL)
        ft_putstr_fd("expected argument to \"unset\"\n", 2);
    else
    {
        while (!args[i++])
            if (unsetenv(args[i]) != 0)
                perror("unsetenv");
    }
    return (1);
}