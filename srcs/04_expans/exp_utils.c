/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:42:41 by julhong           #+#    #+#             */
/*   Updated: 2026/01/17 01:34:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	arr_len(void **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

/** Increaes capacity of a fixed char *array[]
 * - old capacity updated to new capacity
 * - repoints to origianl strings
 * - does not NULL terminate (but there is +1 space for NULL from dup_argv)
 * 
 * Usage:
 * - use in a condition and/or loop to ensure size used can fit in size_cap
 */
char	**realloc_str_arr(char **input, int used, int *old_cap, int new_cap)
{
	char	**new_arr;
	int		i;

	*old_cap = new_cap;
	new_arr = dup_argv(NULL, new_cap);
	i = -1;
	while (++i < used)
		new_arr[i] = input[i];
	free(input);
	return (new_arr);
}

static int	msh_strcmp(const char *a, const char *b)
{
	int		i;
	char	la;
	char	lb;

	i = 0;
	while (a[i] && b[i])
	{
		la = ft_tolower(a[i]);
		lb = ft_tolower(b[i]);
		if (la != lb)
			return ((unsigned char)la - (unsigned char)lb);
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

void	msh_lex_sort(char **argv)
{
	int		cur;
	int		adv;
	int		min;
	char	*tmp;

	cur = 0;
	while (argv[cur] && argv[cur + 1])
	{
		min = cur;
		adv = cur + 1;
		while (argv[adv])
		{
			if (msh_strcmp(argv[min], argv[adv]) > 0)
				min = adv;
			adv++;
		}
		if (min != cur)
		{
			tmp = argv[min];
			ft_memmove(&argv[cur + 1], &argv[cur],
				(min - cur) * sizeof(char *));
			argv[cur] = tmp;
		}
		cur++;
	}
}
