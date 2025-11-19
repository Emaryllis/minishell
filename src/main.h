/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:49:02 by julhong           #+#    #+#             */
/*   Updated: 2025/11/19 03:30:03 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define RST "\033[0m"
# define RD "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;97m"

#define p(...) printf(__VA_ARGS__)

# include <stdbool.h>	// bool type
# include <errno.h>		// errno

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

typedef struct s_st
{
	int		status;
	bool	exit;
}	t_st;

typedef struct s_eof
{
	char	*line;
	bool	eof;
} t_line;

// Parsing Utils
t_line	cell_read_line(void);
t_st	cell_exec(char **args, char **env);

// Builtin Commands
int		cell_echo(char **args);
int		cell_cd(char **args);
int		cell_pwd(char **args);
int		cell_export(char **args);
int		cell_unset(char **args);
int		cell_env(char **args, char **env);
int		cell_exit(char **args);

// Utils
void	print_prompt();
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
#endif
