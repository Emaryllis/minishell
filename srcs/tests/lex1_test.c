/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex1_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:02:09 by julhong           #+#    #+#             */
/*   Updated: 2025/11/25 19:39:58 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

//outputs tokens within a string passed as argv[1]
int main(int ac, char *av[], char *env[])
{
	t_minsh	minsh;

	(void)env;
	if (ac != 2)
		return (1);

	ft_bzero(&minsh, sizeof(t_minsh));
	if (!lex_tokens(&minsh, av[1]))
		return (1);

	for (t_token *tk = minsh.tk_start; tk; tk = tk->next)
		printf("%s\n", tk->str);
	return (0);
}
