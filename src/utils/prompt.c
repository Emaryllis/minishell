/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:18:49 by egoh              #+#    #+#             */
/*   Updated: 2025/11/20 00:25:18 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;

	ptr = (unsigned char *)s;
	value = (unsigned char)c;
	while (n--)
	{
		*ptr = value;
		ptr++;
	}
	return (s);
}

static char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *) &haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

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
	prompt = malloc(total_len + 1);
	if (!prompt)
		return (malloc_error(0), NULL);
	ft_memset(prompt, 0, total_len + 1);
	if (info.user && info.hostname)
	{
		ft_strcat(prompt, "\033[32m");
		ft_strcat(prompt, info.user);
		ft_strcat(prompt, "@");
		ft_strcat(prompt, info.hostname);
		ft_strcat(prompt, "\033[0m:");
	}
	if (info.home && ft_strstr(info.cwd, info.home) == info.cwd)
	{
		ft_strcat(prompt, "\033[34m~");
		ft_strcat(prompt, info.cwd + ft_strlen(info.home));
	}
	else
	{
		ft_strcat(prompt, "\033[34m");
		ft_strcat(prompt, info.cwd);
	}
	ft_strcat(prompt, "\033[0m$ ");
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

	if (!getcwd(cwd, sizeof(cwd)))
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
	return (build_prompt(p, prompt, total_len));
}
