/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:04:08 by julhong           #+#    #+#             */
/*   Updated: 2025/11/25 16:21:38 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static t_token	*last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*new_token(char *src, int len, t_toktype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->str = malloc(len + 1);
	if (!token->str)
		return (NULL);
	ft_memcpy(token->str, src, len);
	token->str[len] = '\0';
	token->type = type;
	token->next = NULL;
	return (token);
}

void	append_token(t_token **start, t_token *new)
{
	t_token	*last;

	if (!start || !new)
		return ;
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	last = last_token(*start);
	last->next = new;
}
