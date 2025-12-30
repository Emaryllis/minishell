/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:05:29 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Converts a string to a long integer.
 * @param s The long integer string
 * @param i Pointer to invalid flag
 * @param r The result accumulator
 * @param sign The sign of the number (1 or -1)
 * @return The converted long integer
 */
static long long	convert(const char *s, bool *i, long long r, int sign)
{
	while (*s)
	{
		if (*s == '\\')
		{
			s++;
			continue ;
		}
		if (*s < '0' || *s > '9')
		{
			*i = true;
			break ;
		}
		if ((sign == 1 && r > (LONG_MAX - (*s - '0')) / 10) || (sign == -1
				&& (t_ull)r > ((t_ull)LONG_MAX + 1 - (*s - '0')) / 10))
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			*i = true;
			return (0);
		}
		r = r * 10 + *s++ - '0';
	}
	return (r * sign);
}

/**
 * Converts a string to a long integer.
 * Sets the invalid flag to true if
 * - The string is not a valid number
 * - The number is out of range (LONG_MIN to LONG_MAX)
 * @param s The long integer string
 * @param invalid Pointer to invalid flag
 * @return The converted long integer
 */
static long int	ft_atoli(const char *s, bool *invalid)
{
	int			sign;
	long long	r;

	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	r = convert(s, invalid, 0, sign);
	if (*invalid)
		return (0);
	return (sign * r);
}

/**
 * Converts
 * @param ms
 * @return
 */
static int	parse_args(t_msh *ms)
{
	long long	code;
	bool		invalid;

	if (!ms->args || !ms->args[1])
		return (INT_MIN);
	if (ms->args[2])
	{
		eprintf("exit\n%s: exit: too many arguments\n", NAME);
		return (INT_MIN + 2);
	}
	invalid = false;
	code = ft_atoli(ms->args[1], &invalid);
	if (invalid)
	{
		eprintf(NAME": exit: %s: numeric argument required\n",
			ms->args[1]);
		return (INT_MIN + 1);
	}
	return ((code % 256 + 256) % 256);
}

/**
 * ms check since cell_exit is used in prompt.c as well
 * Functionalities:
 * - Exit code 2 if the argument is not numeric, or out of range
 * - Print "exit" if in interactive mode
 * - Exits with given or last exit code, or 0 by default
 */
int	cell_exit(t_msh *ms)
{
	int	code;

	if (ms)
	{
		ms->shell_exit = true;
		code = parse_args(ms);
		if (code == INT_MIN + 1)
		{
			set_status(2);
			return (2);
		}
		if (code == INT_MIN + 2)
		{
			set_status(1);
			return (1);
		}
	}
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (ms && code >= 0 && code <= 255)
		return (code);
	if (g_sig.status)
		return (g_sig.status);
	return (EXIT_SUCCESS);
}
