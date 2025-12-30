/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:05:26 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:25:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_eputhex(unsigned long n, int upper)
{
	char	*base;
	int		len;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += ft_eputhex(n / 16, upper);
	len += write(STDERR_FILENO, &base[n % 16], 1);
	return (len);
}

int	ft_eputstr(char *s)
{
	int	len;

	if (!s)
		return (ft_eputstr("(null)"));
	len = 0;
	while (*s)
		len += write(STDERR_FILENO, s++, 1);
	return (len);
}

int	ft_eputnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (write(STDERR_FILENO, "-2147483648", 11));
	if (nb < 0)
	{
		nb = -nb;
		len += write(1, "-", 1);
	}
	if (nb > 9)
		len += ft_eputnbr(nb / 10);
	len += write(STDERR_FILENO, &(char){nb % 10 + '0'}, 1);
	return (len);
}

int	ft_eputunbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_eputunbr(n / 10);
	len += write(STDERR_FILENO, &(char){n % 10 + '0'}, 1);
	return (len);
}
