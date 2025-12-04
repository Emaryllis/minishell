/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/12/04 17:07:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	nmemb;
	char	*dup;

	nmemb = ft_strlen(s) + 1;
	dup = (char *)(malloc(nmemb * sizeof(char)));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, nmemb);
	return (dup);
}

/* char	*ft_strdup(const char *s)
{
	size_t	nmemb;
	char	*dup;
	int		i;

	nmemb = ft_strlen(s) + 1;
	dup = (char *)(malloc(nmemb * sizeof(char)));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
} */

//ema minsh version
char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*copy;

	i = 0;
	while (s[i] && i < n)
		i++;
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
