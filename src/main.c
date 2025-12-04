/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/04 15:22:38 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
 * Cleans up allocated memory for the line and ms structure.
 */
static void	cleanup(char *line, t_ms *ms, char *prompt)
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
	if (ms->exit && ms->env)
	{
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
static bool	init_env(t_ms *ms, char **env)
{
	ms->env = malloc(sizeof(t_array));
	if (!ms->env)
	{
		eprintf("Error getting environment... Exiting.");
		ms->exit = true;
		return (false);
	}
	if (!init_array(ms->env, env))
	{
		eprintf("Error initializing environment... Exiting.");
		ms->exit = true;
		free(ms->env);
		return (false);
	}
	return (true);
}

/**
 * Initializes the ms structure and starts the main loop.
 * After every command execution, it cleans up allocated memory.
 * @see init_env
 * @see cell_read_line
 * @see ft_split
 * @see cell_exec
 * @see cleanup
 */
static void	init_ms(t_ms *ms, char **env)
{
	char	*prompt;
	t_line	line;

	ms->exit = false;
	ms->args = 0;
	if (!init_env(ms, env))
		return ;
	while (!ms->exit)
	{
		prompt = get_prompt();
		line = cell_read_line(prompt);
		if (line.eof)
			ms->exit = true;
		else if (!line.line)
			continue ;
		if (!ms->exit)
		{
			ms->args = ft_split(line.line, ' ');
			if (!ms->args)
				ms->exit = true;
		}
		if (!ms->exit)
			cell_exec(ms);
		cleanup(line.line, ms, prompt);
	}
}

/**
 * The main function of the minishell program.
 * Sets up the prompt, signal handlers, and
 * initializes the ms structure. Once done,
 * it cleans up allocated memory and
 * returns the latest exit status.
 * @return The exit status denoted by {g_sig.status}.
 */
int	main(int c, char **v, char **env)
{
	t_ms	ms;

	setup_signals();
	init_ms(&ms, env);
	return (g_sig.status);
}
