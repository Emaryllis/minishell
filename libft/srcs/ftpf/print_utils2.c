/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:26:51 by julhong           #+#    #+#             */
/*   Updated: 2026/01/03 00:30:26 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_check(int fd, char *str, int str_len, int *printed)
{
	int	ret;

	ret = write(fd, str, str_len);
	if (ret < 0)
		return (-1);
	*printed += ret;
	return (0);
}

static int	print_nchars_check(int fd, char c, int n, int *printed)
{
	int	ret;

	ret = write_nchars(fd, c, n);
	if (ret < 0)
		return (-1);
	*printed += ret;
	return (0);
}

static int	prleft(int fd, int *pr, char *conv, t_pr_segs *pr_segs)
{
	if (write_check(fd, pr_segs->prefix, pr_segs->prfx_len, pr) == -1)
		return (-1);
	if (print_nchars_check(fd, '0', pr_segs->preci_pad, pr) == -1)
		return (-1);
	if (write_check(fd, conv, pr_segs->conv_len, pr) == -1)
		return (-1);
	if (print_nchars_check(fd, ' ', pr_segs->width_pad, pr))
		return (-1);
	return (0);
}

static int	prright(int *pr, char *conv, t_spec *spec, t_pr_segs *pr_segs)
{
	int	fd;

	fd = spec->fd;
	if (!spec->left_0padding)
	{
		if (print_nchars_check(fd, ' ', pr_segs->width_pad, pr) == -1)
			return (-1);
	}
	if (write_check(fd, pr_segs->prefix, pr_segs->prfx_len, pr) == -1)
		return (-1);
	if (spec->left_0padding)
	{
		if (print_nchars_check(fd, '0', pr_segs->width_pad, pr) == -1)
			return (-1);
	}
	if (print_nchars_check(fd, '0', pr_segs->preci_pad, pr) == -1)
		return (-1);
	if (write_check(fd, conv, pr_segs->conv_len, pr) == -1)
		return (-1);
	return (0);
}

int	ftpf_print_fmt(char *conv, t_spec *spec, t_pr_segs *pr_segs)
{
	int	printed;

	printed = 0;
	if (spec->left_justify)
	{
		if (prleft(spec->fd, &printed, conv, pr_segs) == -1)
			return (-1);
	}
	else
	{
		if (prright(&printed, conv, spec, pr_segs) == -1)
			return (-1);
	}
	return (printed);
}
