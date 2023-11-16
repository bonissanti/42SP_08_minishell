/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:36 by brunrodr          #+#    #+#             */
/*   Updated: 2023/11/16 17:03:11 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/segments.h"
#include "../include/hash.h"

t_bool  check_wildcard(char *str)
{
    while (*str)
    {
        if (*str == '*')
            return (true);
        str++;
    }
    return (false);
}

// char    

bool wildcard_match(char *str, char *pattern)
{
    int n = strlen(str);
    int m = strlen(pattern);

    if (m == 0)
        return n == 0;

    bool lookup[n+1][m+1];
    memset(lookup, false, sizeof(lookup));

    lookup[0][0] = true;

    for (int j = 1; j <= m; j++)
        if (pattern[j-1] == '*')
            lookup[0][j] = lookup[0][j-1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pattern[j-1] == '*')
                lookup[i][j] = lookup[i][j-1] || lookup[i-1][j];
            else if (pattern[j-1] == '?' || str[i-1] == pattern[j-1])
                lookup[i][j] = lookup[i-1][j-1];
        }
    }

    return lookup[n][m];
}

int main() {
    char str[] = "fucker";
    char pattern[] = "*cker";
    if (wildcard_match(str, pattern))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}
