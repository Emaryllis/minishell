/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:02:46 by egoh              #+#    #+#             */
/*   Updated: 2026/01/21 21:52:01 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

t_newsig		g_newsig;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_newsig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Writing quit 3 since MACRO for SIGQUIT is 3
/* void	handle_sigquit(int sig)
{
	(void)sig;
	// if (g_sig.child_pid > 0)
	// {
	// 	kill(g_sig.child_pid, SIGQUIT);
	// 	g_sig.status = 128 + SIGQUIT;
	// 	write(1, "Quit: 3\n", 8);
	// 	return ;
	// }
	rl_on_new_line();
	rl_redisplay();
} */

/**
 * Sets up signal handlers for SIGINT and SIGQUIT.
 * Non-interactive mode will follow default behavior.
 * Interactive mode will follow subject's requirements.
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (!isatty(STDIN_FILENO))
		return ;
	g_newsig = 0;
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction SIGINT");
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction SIGQUIT");
}
