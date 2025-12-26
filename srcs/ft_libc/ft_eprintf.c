/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2025/12/17 12:02:24 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_eprintf_utils.h"
#include <stdarg.h>
#include <unistd.h>

static int	pointer_check(va_list args)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (ft_eputstr("(nil)"));
	return (ft_eputstr("0x") + ft_eputhex((unsigned long)ptr, 0));
}

static int	print_format(char c, va_list args)
{
	if (c == 'c')
		return (write(STDERR_FILENO, &(char){va_arg(args, int)}, 1));
	if (c == 's')
		return (ft_eputstr(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_eputnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_eputunbr(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_eputhex(va_arg(args, unsigned int), 0));
	if (c == 'X')
		return (ft_eputhex(va_arg(args, unsigned int), 1));
	if (c == 'p')
		return (pointer_check(args));
	if (c == '%')
		return (write(STDERR_FILENO, "%", 1));
	return (0);
}

int	eprintf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			len += print_format(format[++i], args);
		else
			len += write(STDERR_FILENO, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
