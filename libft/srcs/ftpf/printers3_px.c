/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers3_px.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:31:58 by julhong           #+#    #+#             */
/*   Updated: 2025/07/17 06:26:26 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	init_p_addrpfx(void *p, char **addr, t_pr_segs *pr_segs)
{
	if (!p)
	{
		*addr = "(nil)";
		pr_segs->prefix = "";
	}
	else
	{
		*addr = get_hexstr((uintptr_t)p);
		pr_segs->prefix = "0x";
	}
	pr_segs->prfx_len = ft_strlen(pr_segs->prefix);
	pr_segs->conv_len = ft_strlen(*addr);
}

static void	init_p_segs(t_spec *spec, t_pr_segs *pr_segs)
{
	pr_segs->body_len = pr_segs->prfx_len + pr_segs->conv_len;
	if (spec->fmin_width > pr_segs->body_len)
		pr_segs->width_pad = spec->fmin_width - pr_segs->body_len;
}

int	ftpf_printer_p(va_list *ap, t_spec *spec)
{
	void		*p;
	char		*addr;
	int			printed;
	t_pr_segs	pr_segs;

	p = va_arg(*ap, void *);
	printed = 0;
	ft_bzero(&pr_segs, sizeof(pr_segs));
	init_p_addrpfx(p, &addr, &pr_segs);
	init_p_segs(spec, &pr_segs);
	printed = ftpf_print_fmt(addr, spec, &pr_segs);
	if (p)
		free(addr);
	return (printed);
}

static void	init_x_pfx(unsigned int u, char **s, t_spec *spec, t_pr_segs *segs)
{
	*s = get_hexstr(u);
	if (spec->conv == 'X')
		ft_strupper(*s);
	if (spec->hexa_hash && u != 0)
	{
		if (spec->conv == 'x')
			segs->prefix = "0x";
		else
			segs->prefix = "0X";
	}
	else
		segs->prefix = "";
	segs->prfx_len = ft_strlen(segs->prefix);
	segs->conv_len = ft_strlen(*s);
}

int	ftpf_printer_x(va_list *ap, t_spec *spec)
{
	unsigned int	u;
	char			*hxnbr;
	int				printed;
	t_pr_segs		pr_segs;

	u = va_arg(*ap, unsigned int);
	printed = 0;
	ft_bzero(&pr_segs, sizeof(pr_segs));
	init_x_pfx(u, &hxnbr, spec, &pr_segs);
	ftpf_init_diux_segs(u, spec, &pr_segs);
	printed = ftpf_print_fmt(hxnbr, spec, &pr_segs);
	free(hxnbr);
	return (printed);
}
