/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:23:57 by julhong           #+#    #+#             */
/*   Updated: 2026/01/22 18:16:11 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	collect_hdoc(t_redir **hdoc_start, t_redir *new_hdoc)
{
	t_redir	*last;

	if (!hdoc_start || !new_hdoc)
		return ;
	if (*hdoc_start == NULL)
	{
		*hdoc_start = new_hdoc;
		return ;
	}
	last = *hdoc_start;
	while (last->hdoc_next)
		last = last->hdoc_next;
	last->hdoc_next = new_hdoc;
}

// Need to handle signals here
static void	heredoc(t_redir *cur_redir)
{
	int		pipe_hdoc[2];
	char	*limiter;
	int		lim_len;
	char	*line;

	pipe(pipe_hdoc);
	limiter = cur_redir->target;
	lim_len = ft_strlen(limiter);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			if (isatty(STDIN_FILENO))
				get_next_line(-1);
			break ;
		}
		write(pipe_hdoc[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_hdoc[1]);
	cur_redir->hdoc_pipefd_0 = pipe_hdoc[0];
}

void	resolve_hdocs(t_redir *cur_hdoc)
{
	if (!cur_hdoc)
		return ;
	while (cur_hdoc)
	{
		heredoc(cur_hdoc);
		cur_hdoc = cur_hdoc->hdoc_next;
	}
}
