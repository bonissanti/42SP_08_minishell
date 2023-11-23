#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/exec.h"

t_bool	verify_permissions(const char *file)
{
	if (access(file, F_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		return (false);
	}
	else if (access(file, R_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		return (false);
	}
	else if (access(file, W_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
		return (false);
	}
	return (true);
}

// t_bool	verify_permissions(const char *file)
// {
// 	if (access(file, F_OK) == 0)
// 	{
// 		if (!access(file, R_OK))
// 			ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
// 		else if (!access(file, W_OK))
// 			ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
// 		else if (!access(file, X_OK))
// 			ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
// 		return (true);
// 	}
// 	else
// 	{
// 		ft_fprintf(2, "minishell: %s: %s\n", file, strerror(errno));
// 		return (false);
// 	}
// 	return (true);
// }