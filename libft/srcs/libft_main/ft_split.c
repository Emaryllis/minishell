/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:38:24 by julhong           #+#    #+#             */
/*   Updated: 2025/09/25 23:26:07 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_str_sep(char **str_ptr, char const **s, char c)
{
	char const	*sref;
	int			elm_strlen;

	sref = *s;
	elm_strlen = 0;
	while (*sref && *sref != c)
	{
		elm_strlen++;
		sref++;
	}
	*str_ptr = ft_substr(sref - elm_strlen, 0, elm_strlen);
	if (!*str_ptr)
		return (0);
	*s = sref;
	return (1);
}

//Without ft_strdup
/* static int	set_str_sep(char **str_ptr, char const **s, char c)
{
	char const	*sref;
	int			elm_strlen;
	int			j;

	sref = *s;
	elm_strlen = 0;
	while (*sref && *sref != c)
	{
		elm_strlen++;
		sref++;
	}
	*str_ptr = malloc(elm_strlen + 1);
	if (!*str_ptr)
		return (0);
	(*str_ptr)[elm_strlen] = '\0';
	sref -= elm_strlen;
	j = -1;
	while (*sref && *sref != c)
		(*str_ptr)[++j] = *sref++;
	*s = sref;
	return (1);
} */

char	**ft_split(char const *s, char c)
{
	int		ttl_elms;
	char	**str_ptr;
	int		i;

	ttl_elms = csubstr_sep(s, c);
	str_ptr = ft_calloc(ttl_elms + 1, sizeof(char *));
	if (!str_ptr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		if (!set_str_sep(&str_ptr[i], &s, c))
		{
			free_2darr((void **)str_ptr);
			return (NULL);
		}
		i++;
	}
	return (str_ptr);
}
