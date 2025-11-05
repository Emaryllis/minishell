/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers1_cs_pcent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:31:58 by julhong           #+#    #+#             */
/*   Updated: 2025/07/17 06:25:14 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ftpf_printer_c(va_list *ap, t_spec *spec)
{
	char		c;
	int			printed;
	t_pr_segs	pr_segs;

	c = va_arg(*ap, int);
	printed = 0;
	ft_bzero(&pr_segs, sizeof(pr_segs));
	pr_segs.prefix = "";
	pr_segs.conv_len = 1;
	if (spec->fmin_width > 1)
		pr_segs.width_pad = spec->fmin_width - 1;
	printed = ftpf_print_fmt(&c, spec, &pr_segs);
	return (printed);
}

int	ftpf_printer_pcent(va_list *ap, t_spec *spec)
{
	char		c;
	int			printed;
	t_pr_segs	pr_segs;

	(void)ap;
	c = '%';
	printed = 0;
	ft_bzero(&pr_segs, sizeof(pr_segs));
	pr_segs.prefix = "";
	pr_segs.conv_len = 1;
	if (spec->fmin_width > 1)
		pr_segs.width_pad = spec->fmin_width - 1;
	printed = ftpf_print_fmt(&c, spec, &pr_segs);
	return (printed);
}

int	ftpf_printer_s(va_list *ap, t_spec *spec)
{
	char		*str;
	int			printed;
	t_pr_segs	pr_segs;

	str = va_arg(*ap, char *);
	printed = 0;
	if (!str)
		str = "(null)";
	ft_bzero(&pr_segs, sizeof(pr_segs));
	pr_segs.prefix = "";
	pr_segs.conv_len = (int)ft_strlen(str);
	if (spec->has_precision)
	{
		if (spec->precision == 0)
			pr_segs.conv_len = 0;
		if (spec->precision > 0 && spec->precision < pr_segs.conv_len)
			pr_segs.conv_len = spec->precision;
	}
	if (spec->fmin_width > pr_segs.conv_len)
		pr_segs.width_pad = spec->fmin_width - pr_segs.conv_len;
	printed = ftpf_print_fmt(str, spec, &pr_segs);
	return (printed);
}
