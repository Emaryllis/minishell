/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:49:02 by julhong           #+#    #+#             */
/*   Updated: 2025/11/25 16:24:31 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINSH_H
# define MINSH_H

//Includes: Allowed External Functions
# include <unistd.h>	
//read, write, fork, pipe, dup/2, access, execve
//getcwd, chdir, close, unlink, isatty, ttyname, ttyslot

# include <stdlib.h>	// malloc, free, exit, getenv
# include <stdio.h>		// printf, perror
# include <string.h>	// strerror

# include <fcntl.h>		// open
# include <sys/stat.h>	// stat, lstat, fstat
# include <dirent.h>	// opendir, readdir, closedir

# include <sys/types.h>	// data types for wait/stat e.g. pid/uid/gid_t
# include <sys/wait.h>	// wait, waitpid, wait3, wait4
# include <signal.h>	// signal, sigaction, sigemptyset, sigaddset, kill

# include <termios.h>	// tcsetattr, tcgetattr
# include <sys/ioctl.h>	// ioctl
# include <term.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include <readline/readline.h>  // readline, rl_on_nl/replace_line/redisplay
# include <readline/history.h>   // add_history, rl_clear_history

//Includes: Others
# include "libft.h"
# include <stdbool.h>


//LEXER -----------------------------------------------------------------------

typedef enum e_toktype
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_HERE,
	TK_REDIR_OUT,
	TK_REDIR_APND
}	t_toktype;

typedef struct s_token	t_token;

typedef struct s_token //free node
{
	char		*str; //free string
	t_toktype	type;
	t_token		*next;
}	t_token;

typedef struct s_minsh
{
	t_token	*tk_start;
	int		tk_ttl;
}	t_minsh;

bool	lex_tokens(t_minsh *minsh, char *cur);

//Token Nodes
t_token	*new_token(char *src, int len, t_toktype type);
void	append_token(t_token **start, t_token *new);

//Utils
bool	all_isspace(const char *str);
void	adv_ptr_isspace(char **cur);
void	adv_indx_quote(char *start, int *i, char quote);

//LEXER -----------------------------------------------------------------------

#endif
