/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:36 by julhong           #+#    #+#             */
/*   Updated: 2026/01/03 00:54:42 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_spec
{
	int		fd;
	//flags
	int		int_signpos;	//'+'
	int		int_signspace;	//' '
	int		hexa_hash;		//'#'
	int		left_justify;	//'-'
	int		left_0padding;	//'0'
	//formatting params
	int		fmin_width;			//'x / *'
	int		has_precision;		//'. present?'
	int		precision;		//'.y / .*'
	//conversion
	char	conv;		//'cspdiuxX%'
}	t_spec;

typedef int	(*t_printer)(va_list *, t_spec *);

typedef struct s_ftpf
{
	int		i;
	int		printed;
	int		check;
	t_spec	spec;
}	t_ftpf;

typedef struct s_pr_segs
{
	int		width_pad;
	char	*prefix;
	int		prfx_len;
	int		preci_pad;
	int		conv_len;
	int		body_len;
}	t_pr_segs;

int		ft_printf(const char *s, ...);
int		ft_printfd(int fd, const char *str, ...);
//generic utils
int		is_part(char c, char *charset);
int		write_nchars(int fd, char c, int n);
int		count_base_digits(uintptr_t p, int base);
char	*get_hexstr(uintptr_t p);
//ftpf utils
int		ftpf_parse_fmt(int *i, const char *str, t_spec *spec, va_list *ap);
int		ftpf_print_fmt(char *conv, t_spec *spec, t_pr_segs *pr_segs);
void	ftpf_init_diux_segs(int n, t_spec *spec, t_pr_segs *pr_segs);
//ftpf printer functions
int		ftpf_printer_c(va_list *ap, t_spec *spec);
int		ftpf_printer_s(va_list *ap, t_spec *spec);
int		ftpf_printer_pcent(va_list *ap, t_spec *spec);
int		ftpf_printer_di(va_list *ap, t_spec *spec);
int		ftpf_printer_u(va_list *ap, t_spec *spec);
int		ftpf_printer_p(va_list *ap, t_spec *spec);
int		ftpf_printer_x(va_list *ap, t_spec *spec);

#endif