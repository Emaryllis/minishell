/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/02/07 19:29:02 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Builds a prompt that is identical to
 * the default bash regex prompt of ubuntu.
 * @param info The prompt information
 * @param prompt The prompt string
 * @param total_len The total length of the prompt
 * @return The built prompt string
 */
static char	*build_prompt(t_prompt info, char *prompt, size_t total_len)
{
	prompt = ft_calloc(total_len, sizeof(char));
	if (!prompt)
		return (malloc_error(0), NULL);
	if (info.user && info.hostname)
	{
		ft_strcat(prompt, "\001\033[32m\002");
		ft_strcat(prompt, info.user);
		ft_strcat(prompt, "@");
		ft_strcat(prompt, info.hostname);
		ft_strcat(prompt, "\001\033[0m\002:");
	}
	if (info.home && ft_strstr(info.cwd, info.home) == info.cwd)
	{
		ft_strcat(prompt, "\001\033[34m\002~");
		ft_strcat(prompt, info.cwd + ft_strlen(info.home));
	}
	else
	{
		ft_strcat(prompt, "\001\033[34m\002");
		ft_strcat(prompt, info.cwd);
	}
	ft_strcat(prompt, "\001\033[0m\002$ ");
	return (prompt);
}

/**
 * Builds and returns the prompt string.
 * @return The prompt string.
 * @see build_prompt
 */
static char	*get_prompt(void)
{
	char		*prompt;
	t_prompt	p;
	char		cwd[PATH_MAX];
	size_t		total_len;

	prompt = NULL;
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("getcwd() error");
		return (NULL);
	}
	p = (t_prompt){getenv("USER"), getenv("HOSTNAME"), getenv("HOME"), cwd};
	if (!p.hostname)
		p.hostname = "Minishell";
	total_len = 0;
	if (p.user)
		total_len += ft_strlen(p.user) + ft_strlen(p.hostname) + 20;
	if (p.home && ft_strstr(p.cwd, p.home) == p.cwd)
		total_len += ft_strlen(p.cwd) - ft_strlen(p.home) + 10;
	else
		total_len += ft_strlen(p.cwd) + 10;
	total_len += 3;
	return (build_prompt(p, prompt, total_len));
}

static int	exit_print_if(int is_interactive)
{
	if (!is_interactive)
		return (1);
	ft_printf("exit\n");
	return (1);
}

/** Interactive-aware reader of input from STDIN
 * - Interactively (default) via readline with prompt etc.
 * - Non-inter via gnl (new-malized)
 * - returns t_input with .line and .eof info for caller to action
 * - !buf handles Ctrl+D (EOF) with special print if inter
 */
t_input	cell_read_input(t_msh *ms)
{
	char	*prompt;
	char	*buf;
	int		is_interactive;

	prompt = get_prompt();
	is_interactive = isatty(STDIN_FILENO);
	if (is_interactive && (sigset_msh(1), true))
	{
		buf = readline(prompt);
		sigset_msh(0);
	}
	else
	{
		buf = get_next_line(STDIN_FILENO);
		if (buf && ft_strchr(buf, '\n'))
			buf[ft_strlen(buf) - 1] = '\0';
	}
	msh_consume_sigint(ms);
	if (!buf && exit_print_if(is_interactive))
		return (free(prompt), (t_input){NULL, true});
	if ((buf[0] == '\0' || all_isspace(buf)))
		return (free(prompt), free(buf), (t_input){NULL, false});
	if (is_interactive)
		add_history(buf);
	return (free(prompt), (t_input){buf, false});
}
