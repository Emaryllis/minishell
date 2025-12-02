/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:03:18 by julhong           #+#    #+#             */
/*   Updated: 2025/12/02 23:02:34 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

//temp cntrl-C,D,\ signal handling
static void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char *av[], char *env[])
{
	t_minsh	msh;

	(void)env;
	(void)av;
	if (ac != 1)
		return (1);

	ft_bzero(&msh, sizeof(t_minsh));
	set_signals();

	msh.line = readline("minishell$ ");
	while (msh.line)
	{
		if (*msh.line != '\0' && !all_isspace(msh.line))
			add_history(msh.line);

		//temp lexer
		if (lex_tokens(&msh, msh.line))
		{
			for (t_token *tk = msh.tk_start; tk; tk = tk->next)
				printf("%s\n", tk->str);
		}
		else
			return (1);

		//ast print check;
		build_ast(&msh);
		print_ast(msh.ast_root, 0);

		clear_tokens(&msh.tk_start);

		free(msh.line);
		msh.line = readline("minishell$ ");
	}

	rl_clear_history();

	return (0);
}