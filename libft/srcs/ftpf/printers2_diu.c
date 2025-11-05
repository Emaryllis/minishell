/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers2_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:31:58 by julhong           #+#    #+#             */
/*   Updated: 2025/07/17 06:26:20 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ftpf_init_diux_segs(int n, t_spec *spec, t_pr_segs *pr_segs)
{
	if (spec->has_precision)
	{
		if (spec->precision == 0 && n == 0)
			pr_segs->conv_len = 0;
		else if (spec->precision > pr_segs->conv_len)
			pr_segs->preci_pad = spec->precision - pr_segs->conv_len;
	}
	pr_segs->body_len += pr_segs->prfx_len;
	pr_segs->body_len += pr_segs->preci_pad;
	pr_segs->body_len += pr_segs->conv_len;
	if (spec->fmin_width > pr_segs->body_len)
		pr_segs->width_pad = spec->fmin_width - pr_segs->body_len;
}

static void	init_di_pfx(int n, char **nbr, t_spec *spec, t_pr_segs *pr_segs)
{
	*nbr = ft_itoa(n);
	if (n < 0)
	{
		pr_segs->prefix = "-";
		(*nbr)++;
	}
	else
	{
		if (spec->int_signspace)
			pr_segs->prefix = " ";
		else if (spec->int_signpos)
			pr_segs->prefix = "+";
		else
			pr_segs->prefix = "";
	}
	pr_segs->prfx_len = ft_strlen(pr_segs->prefix);
	pr_segs->conv_len = ft_strlen(*nbr);
}

int	ftpf_printer_di(va_list *ap, t_spec *spec)
{
	int			n;
	char		*nbr;
	int			printed;
	t_pr_segs	pr_segs;

	n = va_arg(*ap, int);
	printed = 0;
	ft_bzero(&pr_segs, sizeof(pr_segs));
	init_di_pfx(n, &nbr, spec, &pr_segs);
	ftpf_init_diux_segs(n, spec, &pr_segs);
	printed = ftpf_print_fmt(nbr, spec, &pr_segs);
	free(nbr - (n < 0));
	return (printed);
}

static void	init_u_pfx(unsigned int u, char **nbr, t_pr_segs *pr_segs)
{
	*nbr = ft_uitoa(u);
	pr_segs->prefix = "";
	pr_segs->prfx_len = ft_strlen(pr_segs->prefix);
	pr_segs->conv_len = ft_strlen(*nbr);
}

int	ftpf_printer_u(va_list *ap, t_spec *spec)
{
	unsigned int	u;
	char			*nbr;
	int				printed;
	t_pr_segs		pr_segs;

	u = va_arg(*ap, unsigned int);
	printed = 0;
	ft_bzero(&pr_segs, sizeof(pr_segs));
	init_u_pfx(u, &nbr, &pr_segs);
	ftpf_init_diux_segs(u, spec, &pr_segs);
	printed = ftpf_print_fmt(nbr, spec, &pr_segs);
	free(nbr);
	return (printed);
}
