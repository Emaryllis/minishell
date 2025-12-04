/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:08:01 by julhong           #+#    #+#             */
/*   Updated: 2025/08/12 15:50:17 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 88
# endif

typedef struct s_gnl_state
{
	char	*stash;
	int		stash_len;
	int		stash_max;
}	t_gnl_state;

typedef struct s_gnl_var
{
	char	*readbuf;
	char	*stash_tmp;
	char	*next_line;
	int		nl_len;
	int		read_len;
	int		read_do;
}	t_gnl_var;

char	*get_next_line(int fd);

//utils
void	*gnlft_memcpy(void *dest, const void *src, size_t n);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s);
void	*gnl_reset(char **stash, char **readbuf);
void	*clear_stashes(t_gnl_state *state_arr);

#endif