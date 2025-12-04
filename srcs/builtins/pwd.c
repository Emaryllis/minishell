/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:06:27 by egoh              #+#    #+#             */
/*   Updated: 2025/12/04 23:03:33 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	cell_pwd(t_msh *ms)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	pwd = get_env(ms->env, "PWD");
	if (pwd && pwd[0] == '/')
	{
		printf("%s\n", pwd);
		return (EXIT_SUCCESS);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
