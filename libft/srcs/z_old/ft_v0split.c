/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v0split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/09/25 22:58:06 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	count_substrs(const char *str, char sep)
{
	int	i;
	int	count;
	int	in_substr;

	i = 0;
	count = 0;
	in_substr = 0;
	while (str[i])
	{
		if (!(str[i] == sep))
		{
			if (!in_substr)
			{
				in_substr = 1;
				count++;
			}
		}
		else
			in_substr = 0;
		i++;
	}
	return (count);
}

static char	*alloc_substr(const char *str, char sep, int *i)
{
	int		len;
	char	*substr;

	len = 0;
	while (str[*i + len] != sep && str[*i + len] != '\0')
		len++;
	substr = ft_substr(str, *i, len);
	if (!substr)
		return (NULL);
	*i += len;
	return (substr);
}

static int	fill_arr(char **s_arr, int *j, const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			s_arr[*j] = alloc_substr(str, sep, &i);
			if (!s_arr[*j])
				return (0);
			(*j)++;
		}
		else
			i++;
	}
	s_arr[*j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**s_arr;
	int		s_arr_indx;

	s_arr = (char **)(malloc((count_substrs(s, c) + 1) * sizeof(char *)));
	if (!s_arr)
		return (NULL);
	s_arr_indx = 0;
	if (!fill_arr(s_arr, &s_arr_indx, s, c))
	{
		while (s_arr_indx > 0)
		{
			s_arr_indx--;
			free(s_arr[s_arr_indx]);
		}
		free(s_arr);
		return (NULL);
	}
	return (s_arr);
}

char	**ft_split_res(char const *s, char c, int *res_elems)
{
	char	**s_arr;
	int		s_arr_indx;

	if (res_elems == NULL)
		s_arr = (char **)(malloc((count_substrs(s, c) + 1) * sizeof(char *)));
	else
	{
		*res_elems = count_substrs(s, c);
		s_arr = (char **)(malloc((*res_elems + 1) * sizeof(char *)));
	}
	if (!s_arr)
		return (NULL);
	s_arr_indx = 0;
	if (!fill_arr(s_arr, &s_arr_indx, s, c))
	{
		while (s_arr_indx > 0)
		{
			s_arr_indx--;
			free(s_arr[s_arr_indx]);
		}
		free(s_arr);
		return (NULL);
	}
	return (s_arr);
}
