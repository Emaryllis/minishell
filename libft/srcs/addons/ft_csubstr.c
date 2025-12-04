/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:04 by julhong           #+#    #+#             */
/*   Updated: 2025/09/25 23:26:15 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	csubstr_sep(const char *str, char sep)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != sep)
		{
			count++;
			while (*str && *str != sep)
				str++;
		}
		else
		{
			while (*str == sep)
				str++;
		}
	}
	return (count);
}

int	csubstr_isp(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (!ft_isspace(*str))
		{
			count++;
			while (*str && !ft_isspace(*str))
				str++;
		}
		else
		{
			while (ft_isspace(*str))
				str++;
		}
	}
	return (count);
}

int	csubstr_chset(const char *str, const char *chset)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (!ft_strchr(chset, *str))
		{
			count++;
			while (*str && !ft_strchr(chset, *str))
				str++;
		}
		else
		{
			while (*str && ft_strchr(chset, *str))
				str++;
		}
	}
	return (count);
}
