/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:02:46 by egoh              #+#    #+#             */
/*   Updated: 2026/01/25 21:39:16 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

t_newsig		g_newsig;

static void	shell_sigint_handler(int sig)
{
	(void)sig;
	g_newsig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

static void	hdoc_sigint_handler(int sig)
{
	(void)sig;
	g_newsig = SIGINT;
	write(1, "\n", 1);
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
 * prompt_type == 0 -> main prompt loop
 * prompt_type == 1 -> hdoc fork
 */
void	sigset_shell(int prompt_type)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (!isatty(STDIN_FILENO))
		return ;
	if (prompt_type == 0)
		sa_int.sa_handler = shell_sigint_handler;
	else
		sa_int.sa_handler = hdoc_sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction SIGINT");
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction SIGQUIT");
}

void	sigset_child_dfl(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (!isatty(STDIN_FILENO))
		return ;
	sa_int.sa_handler = SIG_DFL;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction SIGINT");
	sa_quit.sa_handler = SIG_DFL;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction SIGQUIT");
}

/** Sets a signal disposition for sig_type 
 * dispo == 0 -> SIG_DFL
 * dispo == 1 -> SIG_IGN
 */ 
void	sigset_generic(int sig_type, int dispo)
{
	struct sigaction	sa_sig;
	
	if (!isatty(STDIN_FILENO))
		return ;
	if (dispo == 0)
		sa_sig.sa_handler = SIG_DFL;
	else
		sa_sig.sa_handler = SIG_IGN;
	sa_sig.sa_flags = 0;
	sigemptyset(&sa_sig.sa_mask);
	if (sigaction(sig_type, &sa_sig, NULL) == -1)
		perror("sigaction SIGINT");
}
