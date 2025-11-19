/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/19 19:29:10 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	cleanup(char *line, char **args)
{
	char	**tmp;

	if (args)
	{
		tmp = args;
		while (*tmp)
			free(*tmp++);
		free(args);
	}
	free(line);
}

int	main(int c, char **v, char **env)
{
	t_line	line;
	char	**args;
	t_st	ret;

	ret = (t_st){EXIT_SUCCESS, false};
	while (!ret.exit)
	{
		line = cell_read_line();
		if (line.eof)
			break ;
		if (!line.line)
			continue ;
		args = ft_split(line.line, ' ');
		if (!args)
		{
			free(line.line);
			break ;
		}
		ret = cell_exec(args, env);
		cleanup(line.line, args);
	}
	return (ret.status);
}
