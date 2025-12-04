/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/05/21 17:04:58 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	*next;
	int		len;

	len = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)s + ft_strlen(s));
	res = NULL;
	while (--len >= 0)
	{
		next = ft_strchr(&s[len], c);
		if (next)
		{
			res = next;
			break ;
		}
	}
	return (res);
}
