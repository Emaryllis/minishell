/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:08:01 by julhong           #+#    #+#             */
/*   Updated: 2025/08/12 15:51:40 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*peel(t_gnl_state *state, t_gnl_var *var)
{
	var->nl_len = (var->next_line - state->stash) + 1;
	var->next_line = malloc(var->nl_len + 1);
	if (!var->next_line)
		return (gnl_reset(&state->stash, &var->readbuf));
	gnlft_memcpy(var->next_line, state->stash, var->nl_len);
	var->next_line[var->nl_len] = '\0';
	state->stash_len -= var->nl_len;
	gnlft_memcpy(state->stash, state->stash + var->nl_len, state->stash_len);
	state->stash[state->stash_len] = '\0';
	free(var->readbuf);
	return (var->next_line);
}

static int	update_stash(t_gnl_state *state, t_gnl_var *var)
{
	if (state->stash_len + var->read_len > state->stash_max)
	{
		if (state->stash_len + var->read_len >= state->stash_max * 2)
			state->stash_max = state->stash_len + var->read_len;
		else
			state->stash_max = state->stash_max * 2;
		var->stash_tmp = malloc(state->stash_max + 1);
		if (!var->stash_tmp)
			return (0);
		gnlft_memcpy(var->stash_tmp, state->stash, state->stash_len);
		var->stash_tmp[state->stash_len] = '\0';
		free(state->stash);
		state->stash = var->stash_tmp;
	}
	gnlft_memcpy(state->stash + state->stash_len, var->readbuf, var->read_len);
	state->stash[state->stash_len + var->read_len] = '\0';
	state->stash_len += var->read_len;
	return (1);
}

static int	read_and(t_gnl_state *state, t_gnl_var *var, int fd)
{
	var->read_len = read(fd, var->readbuf, BUFFER_SIZE);
	if (var->read_len < 0)
		return (-1);
	var->readbuf[var->read_len] = '\0';
	if (var->read_len > 0)
	{
		if (update_stash(state, var))
			return (0);
		else
			return (-1);
	}
	if (state->stash && *(state->stash))
	{
		var->next_line = gnl_strdup(state->stash);
		gnl_reset(&state->stash, &var->readbuf);
		return (1);
	}
	return (-1);
}

static int	gnl_init(t_gnl_state *state, t_gnl_var *var, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (state->stash == NULL)
	{
		state->stash = gnl_strdup("");
		state->stash_len = 0;
		state->stash_max = 0;
	}
	var->readbuf = malloc(BUFFER_SIZE + 1);
	if (!var->readbuf)
	{
		gnl_reset(&state->stash, &var->readbuf);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl_state	state_arr[1024];
	t_gnl_var			var;

	if (fd == -1)
		return (clear_stashes(state_arr));
	if (!gnl_init(&state_arr[fd], &var, fd))
		return (NULL);
	while (1)
	{
		var.next_line = gnl_strchr(state_arr[fd].stash, '\n');
		if (var.next_line)
			return (peel(&state_arr[fd], &var));
		var.read_do = read_and(&state_arr[fd], &var, fd);
		if (var.read_do == -1)
			return (gnl_reset(&state_arr[fd].stash, &var.readbuf));
		if (var.read_do == 1)
			return (var.next_line);
	}
}
