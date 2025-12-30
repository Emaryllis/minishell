/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:18:49 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
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
char	*get_prompt(void)
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
