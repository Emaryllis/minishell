/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/05/19 16:02:04 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		front;
	int		back;
	int		len;

	front = 0;
	back = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[front]))
		front++;
	while (ft_strchr(set, s1[back]))
		back--;
	if (front > back)
		len = 0;
	else
		len = back - front + 1;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[front], len + 1);
	return (res);
}

/* char    *ft_strtrim(char const *s1, char const *set)
{
	char    *s;
	char    *res;
	int		read;
	int		write;

	s = ft_strdup(s1);
	read = 0;
	write = 0;
	while (s[read])
	{
		if (ft_strchr(set, s[read]) == NULL)
		{
			s[write] = s[read];
			write++;
		}
		read++;
	}
	s[write] = '\0';
	res = ft_strdup(s);
	free(s);
	return (res);
} */
