/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:21:31 by julhong           #+#    #+#             */
/*   Updated: 2025/06/02 15:04:38 by julhong          ###   ########.fr       */
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
	int		i;
	int		printed;
	int		check;
	t_spec	spec;
	va_list	ap;

	i = 0;
	printed = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
			printed += write(1, &str[i++], 1);
		else
		{
			if (ftpf_parse_fmt(&i, str, &spec, &ap) == -1)
				return (-1);
			check = g_printer_dispatch[(int)spec.conv](&ap, &spec);
			if (check == -1)
				return (-1);
			printed += check;
		}
	}
	va_end(ap);
	return (printed);
}
