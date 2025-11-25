/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:03:18 by julhong           #+#    #+#             */
/*   Updated: 2025/11/25 19:02:47 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	rl_replace_line("", 0);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	set_signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = handle_sigint;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

// bool	all_isspace(const char *str)
// {
// 	while (*str)
// 	{
// 		if (!ft_isspace(*str))
// 			return (false);
// 		str++;
// 	}
// 	return (true);
// }

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