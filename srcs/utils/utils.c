/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// Needs to be atomic safe
void	set_status(int status)
{
	g_sig.status = status;
}

void	debug_print(const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	if (DEBUG)
		printf(format, va);
	va_end(va);
}

int	malloc_error(int ret)
{
	eprintf(NAME": malloc: Cannot allocate memory\n");
	set_status(EXIT_FAILURE);
	return (ret);
}

int	malloc_fail_exit(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

/** Only used in cell_cd */
int	handle_error(char *target, const char *format, t_msh *ms)
{
	char	*env;

	if (!ms)
	{
		eprintf(format);
		free(target);
		return (EXIT_FAILURE);
	}
	env = NULL;
	if (ms->args[1] && ms->env && ft_strcmp(ms->args[1], "-") == 0)
		env = get_env(ms->env, "OLDPWD");
	else if (ms->args[1] && ms->env && ft_strcmp(ms->args[1], "~") == 0)
		env = get_env(ms->env, "HOME");
	if (errno == EACCES)
		eprintf(NAME": cd: %s: Permission denied\n", target);
	else if (env)
		eprintf(NAME": cd: %s: No such file or directory\n", env);
	else if (ms->args[1])
		eprintf(NAME": cd: %s: No such file or directory\n", ms->args[1]);
	free(target);
	return (EXIT_FAILURE);
}
