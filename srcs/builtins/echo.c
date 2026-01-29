/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:06:52 by egoh              #+#    #+#             */
/*   Updated: 2026/01/29 20:51:56 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static int	is_n_flag(const char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	cell_echo(t_msh *ms)
{
	int		i;
	bool	nl;

	i = 1;
	nl = true;
	while (ms->args[i] && is_n_flag(ms->args[i]))
	{
		nl = false;
		i++;
	}
	while (ms->args[i])
	{
		if (ms->args[i][0] != '\0')
		{
			ft_printf("%s", ms->args[i]);
			if (ms->args[i + 1])
				ft_printf(" ");
		}
		i++;
	}
	if (nl)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
