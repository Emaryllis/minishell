/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:05:29 by egoh              #+#    #+#             */
/*   Updated: 2025/11/25 21:05:50 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static	int	convert(const char *s, bool *invalid, int sign, int *len)
{
	long	r;

	r = 0;
	while ((*s >= '0' && *s <= '9') || *s == '\\')
	{
		if (*s == '\\')
			s++;
		r = r * 10 + *s++ - '0';
		*len++;
		if (sign * r > INT_MAX || sign * r < INT_MIN)
		{
			*invalid = true;
			return (0);
		}
	}
	return (r);
}

static int	ft_atoi(const char *s, bool *invalid)
{
	int		len;
	int		sign;
	long	r;

	sign = 1;
	len = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	r = convert(s, invalid, sign, &len);
	if (*invalid)
		return (0);
	if ((!(*s >= '0' && *s <= '9') && *s != '\0') || len >= 10)
	{
		*invalid = true;
		return (0);
	}
	return (sign * (int)r);
}

static int	parse_args(t_ms *ms)
{
	int		code;
	bool	invalid;

	if (!ms->args || !ms->args[1])
		return (INT_MIN);
	invalid = false;
	code = ft_atoi(ms->args[1], &invalid);
	if (invalid)
		return (INT_MIN + 1);
	while (code < 0)
		code += 256;
	return (code % 256);
}

/**
 * ms check since cell_exit is used in prompt.c as well
 * Functionalities:
 * - Exit code 2 if the argument is not numeric
 * - Print "exit" if in interactive mode
 * - Exits with given or last exit code, or 0 by default
 */
int	cell_exit(t_ms *ms)
{
	int	code;

	if (ms)
	{
		ms->exit = true;
		code = parse_args(ms);
		if (code == INT_MIN + 1)
		{
			eprintf(NAME": exit: %s: numeric argument required\n",
				ms->args[1]);
			set_status(2);
			return (2);
		}
	}
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (code && code >= 0 && code <= 255)
		return (code);
	if (g_sig.status)
		return (g_sig.status);
	return (EXIT_SUCCESS);
}
