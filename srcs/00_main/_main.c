/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/29 17:27:36 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

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
 * Everything to initialize.
 * - Writing tool tips is fun
 */
static void	init_state(t_msh *ms, int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_newsig = 0;
	sigset_msh(0);
	ft_bzero(ms, sizeof(t_msh));
	if (!init_env(ms, envp))
		exit(EXIT_FAILURE);
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
	while (!ms->shell_exit)
	{
		ms->input = cell_read_input(ms);
		if (ms->input.eof)
		{
			ms->shell_exit = true;
			main_cleanup(ms);
		}
		else if (!ms->input.line)
			continue ;
		if (!ms->shell_exit && lex_tokens(ms, ms->input.line))
		{
			debug_lex_pr_tk(ms);
			ms->ast_root = build_ast(ms);
			if (!ms->ast_root && main_cleanup(ms))
				continue ;
			debug_print_ast(ms->ast_root, 0);
			execute_ast(ms);
			main_cleanup(ms);
		}
		else if (!ms->shell_exit)
			continue ;
	}
	rl_clear_history();
}

/**
 * The main function of the minishell program.
 * Sets everything up: struct, signals, env, prompt etc.
 * Prompts on loop until expected termination
 * @return The latest exit status denoted by {ms.exstat}.
 */
int	main(int ac, char *av[], char *envp[])
{
	t_msh	ms;

	init_state(&ms, ac, av, envp);
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
		return (parseCFlag(av[2], &ms));
	ms_prompt_loop(&ms);
	return (ms.exstat);
}
