#include "libft.h"

void	ft_printf_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_fprintf(2, "fd didn't have any lines to print.\n");
		return ;
	}
	while (line)
	{
		ft_fprintf(2, "es: %s", line);
		line = get_next_line(fd);
	}
	ft_fprintf(2, "____________________\n");
}
