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

char *join_segments(t_segment *head)
{
	t_segment *current;
	char *str;
	char *ptr;
	int len;

	len = 0;
	current = head;
	while (current)
	{
		len += ft_strlen(current->str);
		current = current->next;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	ptr = str;
	current = head;
	while (current)
	{
		strcpy(ptr, current->str);
		ptr += ft_strlen(current->str);
		current = current->next;
	}
	*ptr = '\0';
	return (str);
}

void	free_segments(t_segment *head)
{
	t_segment *current;
	t_segment *next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	parse_quotes(t_hashtable *env, char **args)
{
	int length;
	char *ptr;
	char quote;
	char *segment;
	t_segment *head;

	t_hash *hash;
	char *key;
	int key_len;

	length = 0;
	head = NULL;
	ptr = *args;
	segment = (char *)malloc(sizeof(char) * ft_strlen(ptr) + 1);
	while (*ptr)
	{
		if (*ptr == '\'' || *ptr == '\"')
		{
			quote = *ptr;
			ptr++;
			while (*ptr != quote)
			{
				if (*ptr == '$' && quote == '\"')
				{
					segment[length] = '\0';
					add_segments(&head, segment);
					length = 0;
					ptr++;
					key_len = strcspn(ptr, " \"");
					key = strndup(ptr, key_len);
					hash = search(env, key);
					if (hash != NULL)
						add_segments(&head, hash->value);
					free(key);
					ptr += key_len;

				}
				else
					segment[length++] = *ptr++;
			}
			ptr++;
		
		}
		else if (*ptr == '$')
		{
			segment[length] = '\0';
			add_segments(&head, segment);
			length = 0;
			ptr++;
			key_len = strcspn(ptr, " \""); //implementar o ft_strcspn com mensagem de erro se não encontrar o caractere
			key = strndup(ptr, key_len);
			hash = search(env, key);
			if (hash != NULL)
				add_segments(&head, hash->value);
			free(key);
			ptr += key_len;
		}
		else
			segment[length++] = *ptr++;
	}
	segment[length] = '\0';
	add_segments(&head, segment);
	free(segment);
	*args = join_segments(head);
	free_segments(head);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_hashtable *env = create_hashtable();
	init_hash(env, envp);
	insert(env, "VAR1", "value1");
	insert(env, "VAR2", "value2");

	char *arg1[] = {"echo", "$VAR1", "$USER", "'$USER", "'''''\"$USER\"'''", NULL}; //tratar fechamento e quando passamos " '' "
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

	destroy_hashtable(env);
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