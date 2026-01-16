/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_expans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:42:26 by julhong           #+#    #+#             */
/*   Updated: 2026/01/17 01:50:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	debug_pr_fargv(char **fargv)
{
	int	i;

	if (!DEBUG)
		return ;
	ft_printf("***DEBUG*** String Expansion:\n");
	i = -1;
	while (fargv[++i])
		ft_printf("final_argv[%i] -- %s\n", i, fargv[i]);
	ft_printf("\n");
}
