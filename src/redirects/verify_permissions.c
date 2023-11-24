#include "../include/builtins.h"
#include "../include/segments.h"
#include "../include/exec.h"

t_bool	verify_file_permissions(const char *file)
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

int verify_cmd_permissions(const char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		// ft_fprintf(2, "minishell: %s: %s\n", cmd, strerror(errno));
		return (126);
	}
	else if (access(cmd, X_OK) != 0)
	{
		// ft_fprintf(2, "minishell: %s: %s\n", cmd, strerror(errno));
		return (127);
	}
	return (0);
}

// t_bool	verify_file_permissions(const char *file)
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