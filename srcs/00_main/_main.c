/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/11 13:02:13 by julhong          ###   ########.fr       */
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
	if (ms->shell_exit && ms->env)
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
static bool	init_env(t_msh *ms, char **env)
{
	ms->env = malloc(sizeof(t_array));
	if (!ms->env)
	{
		eprintf("Error getting environment... Exiting.");
		ms->shell_exit = true;
		return (false);
	}
	if (!init_array(ms->env, env))
	{
		eprintf("Error initializing environment... Exiting.");
		ms->shell_exit = true;
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
		ms->input = cell_read_input(prompt);
		if (ms->input.eof)
			ms->shell_exit = true;
		else if (!ms->input.line)
			continue ;

		if (lex_tokens(ms, ms->input.line))
		{
			//temp lexer check
			printf("Tokens:\n");
			for (t_token *tk = ms->tk_start; tk; tk = tk->next)
				printf("%s\n", tk->str);
			printf("\n");

			build_ast(ms);
			if (!ms->ast_root)
			{
				clear_tokens(&ms->tk_start);
				continue ;
			}
			print_ast(ms->ast_root, 0);
			clear_tokens(&ms->tk_start);
		}
		else
			continue ;

		//EMA get arguments & exec
		//get arguments
		if (!ms->shell_exit)
		{
			ms->args = ft_split(ms->input.line, ' ');
			if (!ms->args)
				ms->shell_exit = true;
		}
		//execute
		if (!ms->shell_exit)
			cell_exec(ms);

		cleanup(ms->input.line, ms, prompt);
	}
}

/**
 * Everything to initialize.
 * - Writing tool tips is fun
 */
static bool	init_state(t_msh *ms, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_bzero(ms, sizeof(t_msh));
	setup_signals();
	if (!init_env(ms, env))
		return (false);
	return (true);
}

/**
 * The main function of the minishell program.
 * Sets everything up: struct, signals, env, prompt etc.
 * Prompts on loop until expected termination
 * @return The latest exit status denoted by {g_sig.status}.
 */
int	main(int ac, char *av[], char *env[])
{
	t_msh	ms;

	if (init_state(&ms, ac, av, env))
		ms_prompt_loop(&ms);
	return (g_sig.status);
}
