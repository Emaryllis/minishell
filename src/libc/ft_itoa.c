/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:40:26 by egoh              #+#    #+#             */
/*   Updated: 2025/11/29 03:46:53 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static char	*ft_strdup(const char *s)
{
	int		i;
	char	*copy;

	i = 0;
	while (s[i])
		i++;
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	itoa_isnegative(int *n, int *negative)
{
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
	}
}

static int	itoa_get_length(int n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		negative;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	negative = 0;
	itoa_isnegative(&n, &negative);
	len = itoa_get_length(n) + negative;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (--len >= 0)
	{
		s[len] = n % 10 + '0';
		n /= 10;
	}
	if (negative)
		s[0] = '-';
	return (s);
}
