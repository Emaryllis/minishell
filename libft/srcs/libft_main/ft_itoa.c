/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/05/16 15:11:40 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*itoa_0(char **res)
{
	*res = (char *)malloc(2);
	if (!(*res))
		return (NULL);
	(*res)[0] = '0';
	(*res)[1] = '\0';
	return (*res);
}

static int	itoa_neg(long *nbr)
{
	if (*nbr < 0)
	{
		*nbr = -(*nbr);
		return (1);
	}
	return (0);
}

static int	count_digits(long nbr)
{
	int	count;

	if (nbr == 0)
		return (1);
	count = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*res;
	int		neg;
	int		len;

	if (n == 0)
		return (itoa_0(&res));
	nbr = (long)n;
	neg = itoa_neg(&nbr);
	len = neg + count_digits(nbr);
	res = (char *)(malloc((len + 1) * (sizeof(char))));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (nbr > 0)
	{
		res[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
