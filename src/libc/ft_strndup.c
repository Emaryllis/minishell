/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 03:40:03 by egoh              #+#    #+#             */
/*   Updated: 2025/11/26 03:40:03 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

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
