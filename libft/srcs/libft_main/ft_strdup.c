/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/05/14 15:37:33 by julhong          ###   ########.fr       */
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
