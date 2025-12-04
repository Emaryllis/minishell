/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:26:51 by julhong           #+#    #+#             */
/*   Updated: 2025/06/02 14:42:41 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_part(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i++])
			return (1);
	}
	return (0);
}

int	print_nchars(char c, int n)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	while (i++ < n)
		printed += write(1, &c, 1);
	return (printed);
}

int	count_base_digits(uintptr_t p, int base)
{
	int	count;

	if (p == 0)
		return (1);
	count = 0;
	while (p > 0)
	{
		p /= base;
		count++;
	}
	return (count);
}

char	*get_hexstr(uintptr_t p)
{
	int			len;
	char		*hex;
	const char	*hex_tab = "0123456789abcdef";

	len = count_base_digits(p, 16);
	hex = (char *)(malloc((len + 1) * sizeof(char)));
	if (!hex)
		return (NULL);
	hex[len] = '\0';
	while (len > 0)
	{
		len--;
		hex[len] = hex_tab[p % 16];
		p /= 16;
	}
	return (hex);
}
