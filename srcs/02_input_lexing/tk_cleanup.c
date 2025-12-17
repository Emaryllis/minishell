/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:57:44 by julhong           #+#    #+#             */
/*   Updated: 2025/12/17 23:58:22 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	clear_tokens(t_token **start)
{
	t_token	*nxt;

	if (!start)
		return ;
	while (*start)
	{
		nxt = (*start)->next;
		if ((*start)->str)
		{
			free((*start)->str);
			(*start)->str = NULL;
		}
		free(*start);
		*start = nxt;
	}
}
