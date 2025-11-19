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

static char	*build_prompt(t_prompt info, char *prompt, size_t total_len)
{
	prompt = malloc(total_len + 1);
	if (!prompt)
		return (NULL);
	ft_memset(prompt, 0, total_len + 1);
	if (info.user && info.name)
	{
		ft_strcat(prompt, "\033[32m");
		ft_strcat(prompt, info.user);
		ft_strcat(prompt, "@");
		ft_strcat(prompt, info.name);
		ft_strcat(prompt, "\033[0m:");
	}
	if (info.home && ft_strstr(info.cwd, info.home) == info.cwd)
	{
		ft_strcat(prompt, "\033[34m~");
		ft_strcat(prompt, info.cwd + strlen(info.home));
	}
	else
	{
		ft_strcat(prompt, "\033[34m");
		ft_strcat(prompt, info.cwd);
	}
	ft_strcat(prompt, "\033[0m$ ");
	return (prompt);
}

char	*get_prompt(void)
{
	char		*prompt;
	t_prompt	info;
	char		cwd[PATH_MAX];
	size_t		total_len;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd() error");
		return (NULL);
	}
	info = (t_prompt){getenv("USER"), getenv("NAME"), getenv("HOME"), cwd};
	total_len = 0;
	if (info.user && info.name)
		total_len += ft_strlen(info.user) + ft_strlen(info.name) + 20;
	if (info.home && ft_strstr(info.cwd, info.home) == info.cwd)
		total_len += ft_strlen(info.cwd) - ft_strlen(info.home) + 10;
	else
		total_len += ft_strlen(info.cwd) + 10;
	return (build_prompt(info, prompt, total_len));
}
