/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:59 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/14 00:13:04 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_all_env(t_hashtable *hash_table)
{
	int		i;
	char	**keys;
	char	*value;

	keys = copy_all_keys(hash_table);
	bubble_sort(keys, hash_table->num_keys);
	i = -1;
	while (++i < hash_table->num_keys)
	{
		value = search(hash_table, keys[i])->value;
		if (value == NULL)
			ft_printf("declare -x %s\n", keys[i]);
		else
			ft_printf("declare -x %s=\"%s\"\n", keys[i], value);
	}
	free(keys);
}

int	env_syntax_check(t_shell *shell, char *temp, t_env *env)
{
	if (temp && !even_close_quotes((*env).equals_sign[1]))
	{
		shell->cmd_status = 1;
		ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
		free_split((*env).equals_sign);
		return (0);
	}
	if ((*env).equals_sign[1])
	{
		analyzing_quotes(shell->hash, shell, &temp);
		(*env).value = temp;
	}
	if (!valid_identifier_export((*env).key))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid "
			"identifier\n", (*env).key);
		if (temp != (*env).equals_sign[1])
			free(temp);
		free((*env).equals_sign[0]);
		free((*env).equals_sign);
		shell->cmd_status = 1;
		return (2);
	}
	return (1);
}

void	env_handler(t_env *env, char **args, int i, char *temp)
{
	t_hash		*hash;
	t_shell		*shell;
	static int	j;

	(void)temp;
	shell = get_shell();
	hash = search(shell->hash, (*env).key);
	j = 1;
	if (args[j][ft_strlen(args[j]) - 1] == '=')
		env_with_equals(shell, args, i);
	else if ((*env).equals_sign[j] != NULL)
		env_with_value(shell->hash, env);
	else if (hash == NULL)
		insert(shell->hash, (*env).key, NULL);
	if (temp != (*env).equals_sign[j])
		free(temp);
	if ((*env).value)
	{
		free((*env).value);
		(*env).value = NULL;
	}
	free((*env).equals_sign[0]);
	free((*env).equals_sign[1]);
	free((*env).equals_sign);
	i++;
}

void	add_env(t_shell *shell, char **args)
{
	int		i;
	t_env	env;
	int		syntax_status;
	char	*temp;

	env.value = NULL;
	i = 0;
	while (args[++i] != NULL)
	{
		if (ft_strlen(args[i]) == 1 && *args[i] == '=')
			env.equals_sign = ft_split(args[i], '\n');
		else
			env.equals_sign = ft_split(args[i], '=');
		env.key = env.equals_sign[0];
		temp = env.equals_sign[1];
		syntax_status = env_syntax_check(shell, temp, &env);
		if (!syntax_status)
			return ;
		else if (syntax_status == 2)
			continue ;
		env_handler(&env, args, i, temp);
	}
}

void	ft_export(t_shell *shell, char **args)
{
	if (args[1] == NULL || *args[1] == '#')
		print_all_env(shell->hash);
	else
	{
		add_env(shell, args);
		if (shell->cmd_status == 1)
			return ;
	}
	shell->cmd_status = 0;
}
