/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/25 22:36:47 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Cleans up allocated memory for the line and ms structure.
 */
static void	cleanup(char *line, t_msh *ms, char *prompt)
{
	char	**tmp;

	if (ms->args)
	{
		tmp = ms->args;
		while (*tmp)
			free(*tmp++);
		free(ms->args);
		ms->args = NULL;
	}
	if ((ms->shell_exit || ms->input.eof) && ms->env)
	{
		ms->shell_exit = true;
		array_free(ms->env);
		free(ms->env);
	}
	free(line);
	free(prompt);
}

/**
 * Initializes the environment array in the ms structure.
 * @param ms The ms structure to initialize.
 * @param env The environment variables.
 * @return true if successful, false otherwise.
 */
static bool	init_env(t_msh *ms, char **env)
{
	ms->env = malloc(sizeof(t_array));
	if (!ms->env)
	{
		ft_printfd(2, "Error getting environment... Exiting.");
		return (false);
	}
	if (!init_array(ms->env, env))
	{
		ft_printfd(2, "Error initializing environment... Exiting.");
		free(ms->env);
		return (false);
	}
	return (true);
}

/**
 * The main loop.
 * After every command execution, it cleans up allocated memory.
 * @see cell_read_input
 * @see ft_split
 * @see cell_exec
 * @see cleanup
 */
static void	ms_prompt_loop(t_msh *ms)
{
	char	*prompt;

	while (!ms->shell_exit)
	{
		prompt = get_prompt();
		ms->input = cell_read_input(prompt, ms);
		if (ms->input.eof)
		{
			ms->shell_exit = true;
			cleanup(ms->input.line, ms, prompt);
		}
		else if (!ms->input.line)
		{
			free(prompt);
			continue ;
		}

		if (!ms->shell_exit && lex_tokens(ms, ms->input.line))
		{
			if (DEBUG)
				debug_lex_pr_tk(ms);

			ms->ast_root = build_ast(ms);
			if (!ms->ast_root)
			{
				clear_tokens(&ms->tk_start);
				clear_ast_garbage(&ms->ast_garbc);
				cleanup(ms->input.line, ms, prompt);
				continue ;
			}
			debug_print_ast(ms->ast_root, 0);

			execute_input(ms);

			clear_tokens(&ms->tk_start);
			clear_ast_garbage(&ms->ast_garbc);
			cleanup(ms->input.line, ms, prompt);
		}
		else if (!ms->shell_exit)
			continue ;

		// //EMA get arguments & exec
		// //get arguments
		// if (!ms->shell_exit)
		// {
		// 	ms->args = ft_split(ms->input.line, ' ');
		// 	if (!ms->args)
		// 		ms->shell_exit = true;
		// }
		// //execute
		// if (!ms->shell_exit)
		// 	cell_exec(ms);
	}
	rl_clear_history();
}

/** Suppresses Ctrl+C print
 */
static void	tty_settings(void)
{
	struct termios	t;

	(void)t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

/**
 * Everything to initialize.
 * - Writing tool tips is fun
 */
static void	init_state(t_msh *ms, int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_newsig = 0;
	sigset_msh(0);
	tty_settings();
	ft_bzero(ms, sizeof(t_msh));
	if (!init_env(ms, envp))
		exit(EXIT_FAILURE);
}

/**
 * The main function of the minishell program.
 * Sets everything up: struct, signals, env, prompt etc.
 * Prompts on loop until expected termination
 * @return The latest exit status denoted by {g_sig.status}.
 */
int	main(int ac, char *av[], char *envp[])
{
	t_msh	ms;

	init_state(&ms, ac, av, envp);
	ms_prompt_loop(&ms);
	return (ms.exit_status);
}
