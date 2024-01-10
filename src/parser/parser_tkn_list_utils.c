/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:22:03 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/10 19:44:10 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	tkn_list_size(t_tkn_list *tkn_list)
{
	int			total;
	t_tkn_list	*head;

	total = 0;
	head = tkn_list;
	while (head)
	{
		head = head->next;
		total++;
	}
	return (total);
}

t_tkn_list	*new_tkn_list(char *content, t_tkn_type type)
{
	t_tkn_list	*node;

	node = (t_tkn_list *)ft_calloc(1, sizeof(t_tkn_list));
	if (!node)
		return (NULL);
	node->type = type;
	if (type == IDENTIFIER || type == WILD || type == EXPAND)
		node->content = content;
	else
	{
		free(content);
		node->content = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_tkn_list	*last_tkn_list(t_tkn_list *tkn_list)
{
	while (tkn_list->next != NULL)
		tkn_list = tkn_list->next;
	return (tkn_list);
}

void	add_tkn_list(t_tkn_list *new_list, t_shell *shell)
{
	t_tkn_list	*last;

	if (!tkn_list_size(shell->tkn_list))
		shell->tkn_list = new_list;
	else
	{
		last = last_tkn_list(shell->tkn_list);
		last->next = new_list;
		last->next->prev = last;
	}
}

void	free_tkn_list(t_tkn_list *tkn_list)
{
	t_tkn_list	*temp;

	while (tkn_list)
	{
		temp = tkn_list->next;
		ft_safe_free((void **)&tkn_list->content);
		ft_safe_free((void **)&tkn_list);
		tkn_list = temp;
	}
}
