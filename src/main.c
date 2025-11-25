/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/23 15:02:10 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	cleanup(char *line, t_ms *ms)
{
	char	**tmp;

	if (ms->args)
	{
		tmp = ms->args;
		while (*tmp)
			free(*tmp++);
		free(ms->args);
	}
	if (ms->exit && ms->env)
	{
		array_free(ms->env);
		free(ms->env);
	}
	free(line);
}

static bool	init_env(t_ms *ms, char **env)
{
	ms->env = malloc(sizeof(t_array));
	if (!ms->env)
	{
		ms->exit = true;
		return (false);
	}
	if (!init_array(ms->env, env))
	{
		ms->exit = true;
		return (false);
	}
	return (true);
}

static void	init_ms(t_ms *ms, char **env, const char *prompt)
{
	t_line	line;

	ms->exit = false;
	if (!init_env(ms, env))
		return ;
	while (!ms->exit)
	{
		line = cell_read_line(prompt);
		if (line.eof)
			break ;
		if (!line.line)
			continue ;
		ms->args = ft_split(line.line, ' ');
		if (!ms->args)
			return (free(line.line));
		cell_exec(ms);
		cleanup(line.line, ms);
	}
}

int	main(int c, char **v, char **env)
{
	char	*prompt;
	t_ms	ms;

	prompt = get_prompt();
	setup_signals();
	init_ms(&ms, env, prompt);
	free(prompt);
	return (g_sig.status);
}
