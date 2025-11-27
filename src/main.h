/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:49:02 by julhong           #+#    #+#             */
/*   Updated: 2025/11/23 15:17:58 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAIN_H
# define MAIN_H

# define DEBUG true
# define NAME "bash"

# define RST "\033[0m"
# define RD "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;97m"

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

# include <stdint.h>                  // uint8_t, uint32_t, etc.
# include <stdbool.h>                 // bool type
# include <errno.h>                   // errno
# include <limits.h>                  // INT_MAX, INT_MIN
# include "libc/eprintf/ft_eprintf.h" // eprintf

// sig_atomic_t guarantees atomic read/write operations
typedef struct s_sig
{
	volatile sig_atomic_t	child_pid;
	volatile sig_atomic_t	status;
}	t_sig;

extern volatile t_sig	g_sig;

typedef struct s_prompt
{
	char	*user;
	char	*hostname;
	char	*home;
	char	*cwd;
}	t_prompt;

typedef struct s_eof
{
	char	*line;
	bool	eof;
}	t_line;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_array
{
	t_env	*data;
	size_t	used_slots;
	size_t	capacity;
}	t_array;

typedef struct s_minishell
{
	char	**args;
	t_array	*env;
	bool	exit;
}	t_ms;

// utils/parse.c, utils/cell.c
t_line	cell_read_line(const char *prompt);
void	cell_exec(t_ms *ms);

// builtins/
int		cell_echo(t_ms *ms);
int		cell_cd(t_ms *ms);
int		cell_pwd(t_ms *ms);
int		cell_export(t_ms *ms);
int		cell_unset(t_ms *ms);
int		cell_env(t_ms *ms);
int		cell_exit(t_ms *ms);

// utils/signal.c
void	setup_signals(void);

// utils/prompt.c, utils/utils.c
char	*get_prompt(void);
void	set_status(int status);

// Dynamic array functions (utils/array/)
bool	init_array(t_array *arr, char **data);
bool	array_push(t_array *arr, t_env elem, bool lazy);
bool	array_remove(t_array *arr, char *key);
void	array_free(t_array *arr);
char	*get_env(t_array *env, const char *key);
bool	set_env(t_array *env, const char *key, const char *value);
bool	convert_all_env(t_ms *ms);
bool	split_env(const char *str, char **key, char **value);
bool	is_env_var(const char *str, bool dollar_sign);

// Libc functions
void	ft_bzero(void *s, size_t len);
void	*ft_calloc(size_t amt, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s, size_t n);
#endif
