/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:59:09 by julhong           #+#    #+#             */
/*   Updated: 2025/08/28 17:02:52 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_invalid_base(char *base, int len)
{
	int	head;
	int	parse;

	head = 0;
	while (head < len - 1)
	{
		parse = head + 1;
		while (parse < len)
		{
			if (base[head] == base[parse])
				return (1);
			if (base[head] == '+' || base[head] == '-' || base[head] <= 32)
				return (1);
			parse++;
		}
		head++;
	}
	if (base[head] == '+' || base[head] == '-' || base[head] <= 32)
		return (1);
	return (0);
}

static int	start_index(char *str, long *neg_sign)
{
	int	i;
	int	neg_count;

	i = 0;
	neg_count = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg_count++;
		i++;
	}
	if (neg_count % 2 != 0)
		*neg_sign = -1;
	return (i);
}

static int	is_base(char c, long *base_index, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
		{
			*base_index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int	*ft_atoi_base(char *str, char *base, int *decimal_nbr)
{
	long		neg_sign;
	long		base_len;
	long		final_num;
	long		i;
	long		base_index;

	neg_sign = 1;
	i = start_index(str, &neg_sign);
	base_len = ft_strlen(base);
	if (base_len < 2 || is_invalid_base(base, base_len))
		return (NULL);
	final_num = 0;
	base_index = 0;
	while (is_base(str[i], &base_index, base))
	{
		final_num = final_num * base_len + base_index;
		i++;
	}
	final_num = final_num * neg_sign;
	if (!(final_num >= -2147483648 && final_num <= 2147483647))
		return (NULL);
	*decimal_nbr = final_num;
	return (decimal_nbr);
}
