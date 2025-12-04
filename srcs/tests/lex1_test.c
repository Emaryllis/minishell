/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex1_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:02:09 by julhong           #+#    #+#             */
/*   Updated: 2025/12/04 23:04:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

//outputs tokens within a string passed as argv[1]
int main(int ac, char *av[], char *env[])
{
	t_msh	msh;

	(void)env;
	if (ac != 2)
		return (1);

	ft_bzero(&msh, sizeof(t_msh));
	if (!lex_tokens(&msh, av[1]))
		return (1);

	for (t_token *tk = msh.tk_start; tk; tk = tk->next)
		printf("%s\n", tk->str);
	return (0);
}
