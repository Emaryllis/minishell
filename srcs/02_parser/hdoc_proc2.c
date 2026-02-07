/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_proc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:23:18 by julhong           #+#    #+#             */
/*   Updated: 2026/02/07 15:31:53 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

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

static bool	init_hdoc(t_hdoc *hd, t_redir *r)
{
	if (pipe(hd->pfds) == -1)
		return (perror(NAME": pipe"), false);
	hd->do_expans = !(ft_strchr(r->target, '\'') || ft_strchr(r->target, '"'));
	r->hd_expans = hd->do_expans;
	hd->lim = hdoc_lim_strip(r->target);
	hd->lim_len = ft_strlen(hd->lim);
	return (true);
}

int	heredoc_notatty(t_redir *r, t_msh *ms, int fd)
{
	t_hdoc	h;

	if (!init_hdoc(&h, r))
		return (EXIT_FAILURE);
	h.line = get_next_line(fd);
	while (h.line)
	{
		if (ft_strncmp(h.line, h.lim, h.lim_len) == 0
			&& h.line[h.lim_len] == '\n')
		{
			free(h.line);
			break ;
		}
		if (fd != STDIN_FILENO && h.do_expans)
			h.line = expand_str_envs(h.line, ms, 1);
		write(h.pfds[1], h.line, ft_strlen(h.line));
		free(h.line);
		h.line = get_next_line(fd);
	}
	if (free(h.lim), fd_clset(&h.pfds[1]))
		r->hd_pfd_0 = h.pfds[0];
	return (EXIT_SUCCESS);
}

static void	hdoc_isatty_loop(t_hdoc hd)
{
	while (1)
	{
		hd.line = readline("> ");
		if (!hd.line
			|| (ft_strcmp(hd.line, hd.lim) == 0 && (free(hd.line), true)))
			break ;
		write(hd.pfds[WR_END], hd.line, ft_strlen(hd.line));
		write(hd.pfds[WR_END], "\n", 1);
		free(hd.line);
	}
}

int	heredoc_isatty(t_redir *r, t_msh *ms)
{
	t_hdoc	hd;
	pid_t	pid;
	int		wstat;
	int		xstat;

	if (!init_hdoc(&hd, r))
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1 && fd_clstwo(hd.pfds))
		return (perror(NAME": fork"), EXIT_FAILURE);
	if (pid == 0 && fd_clset(&hd.pfds[RE_END]) && sigset_generic(SIGINT, 1))
		hdoc_isatty_loop(hd);
	fd_clset(&hd.pfds[WR_END]);
	free(hd.lim);
	if (pid == 0)
		return (ms->shell_exit = true, main_cleanup(ms), exit(EXIT_SUCCESS), 0);
	waitpid(pid, &wstat, 0);
	xstat = interp_wtstat(wstat);
	if (xstat != EXIT_SUCCESS)
		return (fd_clset(&hd.pfds[RE_END]), EXIT_FAILURE);
	return (r->hd_pfd_0 = hd.pfds[RE_END], EXIT_SUCCESS);
}
