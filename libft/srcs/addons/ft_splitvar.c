/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/09/25 23:30:26 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_str_isp(char **str_ptr, char const **s)
{
	char const	*sref;
	int			elm_strlen;

	sref = *s;
	elm_strlen = 0;
	while (*sref && !ft_isspace(*sref))
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

char	**ft_issplit(char const *s)
{
	int		ttl_elms;
	char	**str_ptr;
	int		i;

	ttl_elms = csubstr_isp(s);
	str_ptr = ft_calloc(ttl_elms + 1, sizeof(char *));
	if (!str_ptr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		if (!set_str_isp(&str_ptr[i], &s))
		{
			free_2darr((void **)str_ptr);
			return (NULL);
		}
		i++;
	}
	return (str_ptr);
}

static int	set_str_chset(char **str_ptr, char const **s, char *chset)
{
	char const	*sref;
	int			elm_strlen;

	sref = *s;
	elm_strlen = 0;
	while (*sref && !ft_strchr(chset, *sref))
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

char	**ft_splitchset(char const *s, char *chset)
{
	int		ttl_elms;
	char	**str_ptr;
	int		i;

	ttl_elms = csubstr_chset(s, chset);
	str_ptr = ft_calloc(ttl_elms + 1, sizeof(char *));
	if (!str_ptr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_strchr(chset, *s))
			s++;
		if (!*s)
			break ;
		if (!set_str_chset(&str_ptr[i], &s, chset))
		{
			free_2darr((void **)str_ptr);
			return (NULL);
		}
		i++;
	}
	return (str_ptr);
}
