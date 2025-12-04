/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:11:15 by julhong           #+#    #+#             */
/*   Updated: 2025/12/02 22:29:05 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minsh.h>

bool	all_isspace(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

void	adv_ptr_isspace(char **cur)
{
	char	*start;

	start = *cur;
	while (ft_isspace(*start))
		start++;
	*cur = start;
}

void	adv_indx_quote(char *start, int *i, char quote)
{
	int	cur_indx;

	cur_indx = *i;
	cur_indx++;
	while (start[cur_indx] && start[cur_indx] != quote)
		cur_indx++;
	*i = cur_indx;
}
