/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/02/04 19:52:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	malloc_error(int ret)
{
	ft_printfd(2, NAME": malloc: Cannot allocate memory\n");
	return (ret);
}

int	malloc_fail_exit(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

/**
 * Sets a line from cmd into ms->input.line
 * If semicolon found, sets line up to it
 * If cmd is empty, set eof to true
 * If cmd is has no semicolon, set line to entire cmd
 * Updates the cmd pointer to after the processed line
 * @param cmd The string that holds unparsed commands
 */
char	*parse_c_flag(t_msh *ms, char **cmd)
{
	size_t	i;
	char	*input;

	i = ft_strlen(*cmd);
	input = ft_strchr(*cmd, ';');
	ms->shell_exit = ft_strlen(*cmd) == 0;
	if (ms->shell_exit)
		return (input);
	if (input)
		i = input - *cmd;
	input = ft_substr(*cmd, 0, i);
	*cmd += i;
	if (*cmd && **cmd == ';')
		(*cmd)++;
	if (!ft_strlen(input))
	{
		free(input);
		input = NULL;
	}
	if (DEBUG)
		printf("Parsed cmd input: [%s]\n", input);
	return (input);
}
