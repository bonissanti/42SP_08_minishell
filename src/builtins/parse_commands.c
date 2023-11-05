/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:11:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/01 19:30:44 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "segments.h"

// char *get_key(char *arg);
// char *replace_var(char *arg, t_hash *value);

// void	parse_quotes(t_hashtable *env, char **args)
// {
// 	char *ptr;
// 	char *new_arg;
// 	char quote;
// 	int i;

// 	i = 0;
// 	ptr = *args;
// 	new_arg = (char *)malloc(sizeof(char) * ft_strlen(ptr) + 1);
	
// 	while (*ptr)
// 	{
// 		if (*ptr == '\'' || *ptr == '\"')
// 		{
// 			quote = *ptr;
// 			ptr++;
// 			while (*ptr != quote)
// 			{

// 			}
// 		}
// 	}
// }

t_segment *new_segments(char *str)
{
	t_segment *cmd;

	cmd = (t_segment *)malloc(sizeof(t_segment));
	cmd->str = ft_strdup(str);
	cmd->next = NULL;
	return (cmd);
}

void add_segments(t_segment **head, char *str)
{
	t_segment *current;

	if (*head == NULL)
		*head = new_segments(str);
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_segments(str);
	}
}



int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_hashtable *env = create_hashtable();
	init_hash(env, envp);
	insert_hash(env, "VAR1", "value1");
	insert_hash(env, "VAR2", "value2");

	char *arg1[] = {"echo", "$VAR1", "$USER", "'$USER'", "\"$USER\"", NULL};
	char *arg2[] = {"echo", "$VAR2", "$HOME", "'$HOME'", "\"$HOME\"", NULL};

	int i = 0;
	while (arg1[i] != NULL)
	{
		parse_quotes(env, &arg1[i]);
		i++;
	}

	i = 0;
	while (arg2[i] != NULL)
	{
		parse_quotes(env, &arg2[i]);
		i++;
	}

	i = 0;
	while (arg1[i] != NULL)
		printf("%s ", arg1[i++]);
	printf("\n");

	i = 0;
	while (arg2[i] != NULL)
		printf("%s ", arg2[i++]);
	printf("\n");

	return (0);
}


// while (*ptr != '\0')
// 	{
// 		if (*ptr == '\'' || *ptr == '\"')
// 		{
// 			quote = *ptr;
// 			ptr++;
// 			while (*ptr != quote)
// 				ptr++;
// 		}
// 		else if (*ptr == '$')
// 		{
// 			ptr++;
// 			key = ft_strndup(ptr, ft_strchr(ptr, ' ') - ptr);
// 			value = search(env, key);
// 			if (value != NULL)
// 			{
// 				ft_strcpy(ptr, value);
// 				ptr += ft_strlen(value);
// 			}
// 			else
// 				ptr += ft_strlen(key);
// 		}
// 		ptr++;
// 	}