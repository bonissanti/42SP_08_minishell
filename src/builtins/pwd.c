/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:12:58 by brunrodr          #+#    #+#             */
/*   Updated: 2023/10/19 19:16:23 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <errno.h>

void	ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
}
