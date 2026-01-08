/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_expans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:42:26 by julhong           #+#    #+#             */
/*   Updated: 2026/01/08 23:06:01 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	print_example_expans(char *str, t_msh *ms)
{
	ft_printf("***DEBUG*** String Expansion:\n");
	ft_printf("Unexpanded: %s\n", str);
	str = expand_str_envs(str, ms);
	ft_printf("Expanded: %s\n\n", str);
}
