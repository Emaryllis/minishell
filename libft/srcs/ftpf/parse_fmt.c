/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:10:17 by julhong           #+#    #+#             */
/*   Updated: 2026/01/03 01:00:54 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	check_flags(int *i, const char *str, t_spec *spec)
{
	while (is_part(str[++(*i)], "+ #-0"))
	{
		if (str[*i] == '+')
			spec->int_signpos = 1;
		else if (str[*i] == ' ')
			spec->int_signspace = 1;
		else if (str[*i] == '#')
			spec->hexa_hash = 1;
		else if (str[*i] == '-')
			spec->left_justify = 1;
		else if (str[*i] == '0')
			spec->left_0padding = 1;
	}
}

static void	check_width(int *i, const char *str, t_spec *spec, va_list *ap)
{
	if (str[*i] == '*')
	{
		spec->fmin_width = va_arg(*ap, int);
		(*i)++;
	}
	else
	{
		while (ft_isdigit(str[*i]))
			spec->fmin_width = spec->fmin_width * 10 + str[(*i)++] - '0';
	}
}

static void	check_preci(int *i, const char *str, t_spec *spec, va_list *ap)
{
	if (str[*i] == '.')
	{
		spec->has_precision = 1;
		if (str[++(*i)] == '*')
		{
			spec->precision = va_arg(*ap, int);
			(*i)++;
		}
		else
		{
			while (ft_isdigit(str[*i]))
				spec->precision = spec->precision * 10 + str[(*i)++] - '0';
		}
	}
}

static void	conf_res(t_spec *spec)
{
	if (spec->fmin_width < 0)
	{
		spec->left_justify = 1;
		spec->fmin_width = -spec->fmin_width;
	}
	if (spec->precision < 0)
		spec->has_precision = 0;
	if (spec->left_justify || spec->has_precision)
		spec->left_0padding = 0;
	if (spec->int_signpos)
		spec->int_signspace = 0;
}

int	ftpf_parse_fmt(int *i, const char *str, t_spec *spec, va_list *ap)
{
	int	fd;

	fd = spec->fd;
	ft_bzero(spec, sizeof(*spec));
	spec->fd = fd;
	check_flags(i, str, spec);
	check_width(i, str, spec, ap);
	check_preci(i, str, spec, ap);
	if (is_part(str[*i], "cspdiuxX%"))
		spec->conv = str[(*i)++];
	else
		return (-1);
	conf_res(spec);
	return (0);
}
