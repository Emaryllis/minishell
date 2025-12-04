/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:08:01 by julhong           #+#    #+#             */
/*   Updated: 2025/08/12 15:55:25 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnlft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	*gnl_reset(char **stash, char **readbuf)
{
	free(*readbuf);
	free (*stash);
	*stash = NULL;
	return (NULL);
}

void	*clear_stashes(t_gnl_state *state_arr)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		free(state_arr[i].stash);
		state_arr[i].stash = NULL;
		state_arr[i].stash_len = 0;
		state_arr[i].stash_max = 0;
		i++;
	}
	return (NULL);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*gnl_strdup(const char *s)
{
	size_t	nmemb;
	char	*dup;

	nmemb = 0;
	while (s[nmemb])
		nmemb++;
	dup = (char *)(malloc((nmemb + 1) * sizeof(char)));
	if (!dup)
		return (NULL);
	gnlft_memcpy(dup, s, nmemb);
	dup[nmemb] = '\0';
	return (dup);
}
