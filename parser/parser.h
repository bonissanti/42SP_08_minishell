/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:02:11 by aperis-p          #+#    #+#             */
/*   Updated: 2023/10/26 21:50:04 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * enum: t_precedence_weight
 * -----------------
 *	t_precedence_weight was created to serve
 * 	as a weight chart to the parser do it's
 * 	logic. 
 * 
 * @var: OUTFILE: >.
 * @var: INFILE: <.
 * @var: APPEND_OUTFILE: >>.
 * @var: PARENTHESIS: (.
 * @var: LOGICAL_OR: ||.
 * @var: LOGICAL_AND: &&.
 * @var: PIPE: |.
 * @var: HERE_DOC: <<.
 */

typedef enum {
    OUTFILE = 1,
    INFILE = 2,
    APPEND_OUTFILE = 1,
    PARENTHESIS = 3,
    LOGICAL_OR = 3,
    LOGICAL_AND = 3,
    PIPE = 4,
    HERE_DOC = 5
} 		t_precedence_weight;