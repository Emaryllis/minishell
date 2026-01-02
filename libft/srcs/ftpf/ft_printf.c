/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:21:31 by julhong           #+#    #+#             */
/*   Updated: 2026/01/03 00:54:46 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_printer	g_printer_dispatch[256] = {
['c'] = ftpf_printer_c,
['s'] = ftpf_printer_s,
['%'] = ftpf_printer_pcent,
['d'] = ftpf_printer_di,
['i'] = ftpf_printer_di,
['u'] = ftpf_printer_u,
['p'] = ftpf_printer_p,
['x'] = ftpf_printer_x,
['X'] = ftpf_printer_x};

int	ft_printf(const char *str, ...)
{
	t_ftpf	var;
	va_list	ap;

	var.spec.fd = 1;
	var.i = 0;
	var.printed = 0;
	va_start(ap, str);
	while (str[var.i])
	{
		if (str[var.i] != '%')
			var.printed += write(var.spec.fd, &str[var.i++], 1);
		else
		{
			if (ftpf_parse_fmt(&var.i, str, &var.spec, &ap) == -1)
				return (-1);
			var.check = g_printer_dispatch[(int)var.spec.conv](&ap, &var.spec);
			if (var.check == -1)
				return (-1);
			var.printed += var.check;
		}
	}
	va_end(ap);
	return (var.printed);
}

int	ft_printfd(int fd, const char *str, ...)
{
	t_ftpf	var;
	va_list	ap;

	var.spec.fd = fd;
	var.i = 0;
	var.printed = 0;
	va_start(ap, str);
	while (str[var.i])
	{
		if (str[var.i] != '%')
			var.printed += write(var.spec.fd, &str[var.i++], 1);
		else
		{
			if (ftpf_parse_fmt(&var.i, str, &var.spec, &ap) == -1)
				return (-1);
			var.check = g_printer_dispatch[(int)var.spec.conv](&ap, &var.spec);
			if (var.check == -1)
				return (-1);
			var.printed += var.check;
		}
	}
	va_end(ap);
	return (var.printed);
}
