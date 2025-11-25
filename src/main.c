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
	free(line);
}

static void	init_ms(t_ms *ms, char **env, const char *prompt)
{
	t_line	line;

	ms->env = env;
	ms->exit = false;
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
