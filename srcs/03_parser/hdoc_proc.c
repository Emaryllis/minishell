/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:23:57 by julhong           #+#    #+#             */
/*   Updated: 2026/01/24 01:38:24 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// Collects t_redir nodes of type hdoc in linked list
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

/** Simple quote stripping for heredoc delimiter
 * - a simpler version compared to strip_split_gmark_nxt() in expansion
 * - since the delim is a word token str and is not expanded,
 * 	it will not contain non-quoted spaces and will not be split
 */
static char	*hdoc_lim_strip(char *raw_lim)
{
	char	*out_lim;
	t_quote	quote;
	int		i;

	out_lim = ft_strdup(raw_lim);
	quote = NO_QUOTE;
	i = 0;
	while (*raw_lim)
	{
		if (ft_strchr("'\"", *raw_lim))
			quote_filter(&raw_lim, out_lim, &i, &quote);
		else
			out_lim[i++] = *raw_lim++;
	}
	return (out_lim[i] = '\0', out_lim);
}

static void	init_hdoc(t_hdoc *h, t_redir *r)
{
	pipe(h->hd_pipe);
	h->hd_expans = !(ft_strchr(r->target, '\'') || ft_strchr(r->target, '"'));
	h->limiter = hdoc_lim_strip(r->target);
	h->lim_len = ft_strlen(h->limiter);
}

static void	heredoc_notatty(t_redir *r, t_msh *ms)
{
	t_hdoc	h;

	init_hdoc(&h, r);
	while (1)
	{
		h.line = get_next_line(STDIN_FILENO);
		if (!h.line)
			break ;
		if (ft_strncmp(h.line, h.limiter, h.lim_len) == 0
			&& h.line[h.lim_len] == '\n')
		{
			free(h.line);
			break ;
		}
		if (h.hd_expans)
			h.line = expand_str_envs(h.line, ms, 1);
		write(h.hd_pipe[1], h.line, ft_strlen(h.line));
		free(h.line);
	}
	if (free(h.limiter), close(h.hd_pipe[1]), true)
		r->hdoc_pipefd_0 = h.hd_pipe[0];
}

// Need to handle signals here
static void	heredoc_isatty(t_redir *r, t_msh *ms)
{
	t_hdoc	h;

	init_hdoc(&h, r);
	while (1)
	{
		h.line = readline("> ");
		if ((g_newsig == SIGINT) && (free(h.line), true))
			break ;
		if (!h.line
			|| (ft_strcmp(h.line, h.limiter) == 0 && (free(h.line), true)))
			break ;
		if (h.hd_expans)
			h.line = expand_str_envs(h.line, ms, 1);
		write(h.hd_pipe[1], h.line, ft_strlen(h.line));
		write(h.hd_pipe[1], "\n", 1);
		free(h.line);
	}
	if (free(h.limiter), close(h.hd_pipe[1]), true)
		r->hdoc_pipefd_0 = h.hd_pipe[0];
}

// Input resolution of heredocs sequantially, from hdoc collection
void	resolve_hdocs(t_redir *cur_hdoc, t_msh *ms)
{
	if (!cur_hdoc)
		return ;
	if (isatty(STDIN_FILENO))
		sigset_hdoc();
	while (cur_hdoc)
	{
		if (isatty(STDIN_FILENO))
			heredoc_isatty(cur_hdoc, ms);
		else
			heredoc_notatty(cur_hdoc, ms);
		if (isatty(STDIN_FILENO) && g_newsig == SIGINT)
		{
			sigset_shell();
			rl_done = 0;
			return ;
		}
		cur_hdoc = cur_hdoc->hdoc_next;
	}
}
