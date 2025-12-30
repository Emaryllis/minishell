/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:49:02 by julhong           #+#    #+#             */
/*   Updated: 2025/12/30 15:20:45 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINSH_H
# define MINSH_H

# define DEBUG true
# define NAME "minishell"

//Error Codes -------------------------//
# define MS_ER_BADBLTIN		2
# define MS_ER_NOTEXEC		126
# define MS_ER_CMDNOTF		127
# define MS_ER_SIGINT		130
# define MS_ER_SIGQUIT		131
# define MS_ER_SYNTAX		258

//INCLUDES: Allowed External Functions ----------------------------------------
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

//Includes: OTHERS --------------------//
# include <stdint.h>                   // uint8_t, uint32_t, etc.
# include <stdbool.h>                  // bool type
# include <errno.h>                    // errno
# include <limits.h>                   // INT_MAX, INT_MIN
# include "srcs/ft_libc/ft_eprintf.h"  // eprintf
# include "libft/libft.h"

//Forward Declarations --------------------------------------------------------

typedef struct s_minishell	t_msh;

//PART B: EMA -----------------------------------------------------------------

// sig_atomic_t guarantees atomic read/write operations

typedef struct s_sig
{
	volatile sig_atomic_t	child_pid;
	volatile sig_atomic_t	status;
}	t_sig;

extern volatile t_sig		g_sig;

//To replace global signal
// typedef volatile sig_atomic_t	t_sigat;
// extern t_sigat	g_sig;

typedef struct s_prompt
{
	char		*user;
	char		*hostname;
	char		*home;
	char		*cwd;
}	t_prompt;

typedef struct s_input
{
	char		*line;
	bool		eof;
}	t_input;

typedef unsigned long long	t_ull;

typedef struct s_env
{
	char		*key;
	char		*value;
}	t_env;

typedef struct s_array
{
	t_env		*data;
	size_t		used_slots;
	size_t		capacity;
}	t_array;

// utils/parse.c, utils/cell.c

t_input		cell_read_input(const char *prompt);
void		cell_exec(t_msh *ms);

// builtins/

int			cell_echo(t_msh *ms);
int			cell_cd(t_msh *ms);
int			cell_pwd(t_msh *ms);
int			cell_export(t_msh *ms);
int			cell_unset(t_msh *ms);
int			cell_env(t_msh *ms);
int			cell_exit(t_msh *ms);

// utils/signal.c

void		setup_signals(void);

// utils/prompt.c, utils/utils.c

char		*get_prompt(void);
void		set_status(int status);
int			malloc_error(int ret);
int			handle_error(char *target, const char *format, t_msh *ms);
void		debug_print(const char *format, ...);

// Dynamic array functions (utils/array/)

bool		init_array(t_array *arr, char **data);
bool		array_push(t_array *arr, t_env elem, bool lazy);
bool		array_remove(t_array *arr, char *key);
void		array_free(t_array *arr);
char		*get_env(t_array *env, const char *key);
bool		set_env(t_array *env, const char *key, const char *value);
bool		convert_all_env(t_msh *ms);
int			split_env(const char *str, char **key, char **value);
bool		is_env_var(const char *str, bool dollar_sign);
t_env		*quicksort_env(const t_array *arr);

//PART A: JUL -----------------------------------------------------------------
//LEXER -----------------------------------------------------------------------

typedef enum e_toktype
{
	TK_WORD,
	TK_RDR_IN,
	TK_RDR_HERE,
	TK_RDR_OUT,
	TK_RDR_APND,
	TK_SUBSH_OPN,
	TK_SUBSH_CLS,
	TK_PIPE,
	TK_AND,
	TK_OR
}	t_toktype;

typedef struct s_token		t_token;
typedef struct s_token //FREE token node
{
	char		*str; //FREE string LATER (will be reused in AST)
	t_toktype	type;
	t_token		*next;
}	t_token;

bool		lex_tokens(t_msh *minsh, char *cur);

//Token made to type
t_token		*tk_make_op(char **cur);

//Token raw node data
t_token		*new_token(char *src, int len, t_toktype type);
void		append_token(t_token **start, t_token *new);

//Cleanup
void		clear_tokens(t_token **start);

//Lex utils
bool		all_isspace(const char *str);

//Debugging
void		debug_lex_pr_tk(t_msh *ms);

//PARSER ----------------------------------------------------------------------

typedef enum e_astype
{
	AST_NULL,
	AST_CMD,
	AST_SUBSH,
	AST_PIPE,
	AST_AND,
	AST_OR
}	t_astype;

typedef struct s_redir		t_redir;	//FREE redir node
typedef struct s_redir
{
	t_toktype	type;
	char		*target;				//reuse lexer strs
	t_redir		*next;
}	t_redir;

typedef struct s_ast		t_ast;		//FREE ast node
typedef struct s_ast
{
	t_astype	type;
	t_ast		*left;
	t_ast		*right;

	//CMD Segment
	int			cmd_ac;
	char		**cmd_av;				//FREE outer (inner reuse lexer strs)
	t_redir		*redir_start;

	t_ast		*garbc_nxt;
}	t_ast;

typedef struct s_parse_state
{
	t_token		*cur_tk;
	t_token		*error_tk;
	int			tk_ttl;
	bool		parse_error;
	bool		unexp_end;
	t_ast		**garbc_start;
}	t_parse_state;

t_ast		*build_ast(t_msh *msh);
void		print_ast(t_ast *node, int depth);

//AST leaf exit point
t_ast		*parse_lvl0_cmdseg(t_token **cur_tk, t_parse_state *p_state);

//AST recursive subshell to top level (lvl2 logical)
void		parse_lvl0_subsh(t_token **cur_tk, t_ast *cmd_node,
				t_parse_state *p_state);

//AST nodes
t_ast		*new_ast_node(t_astype type, t_ast **garbc_start);

//Redir nodes (for t_astype == AST_CMD)
t_redir		*new_redir_node(t_toktype type);
void		append_redir(t_redir **start, t_redir *new);

//Cleanup
void		clear_ast_garbage(t_ast **gc_start);

//Syntax Handling
void		set_pstate_err(t_parse_state *p_state);
int			pr_syntax_err(t_parse_state p_state);

//Debugging
void		debug_parse_garbc(t_ast *gc_start);
const char	*get_ast_type(t_astype type);

//EXEC ------------------------------------------------------------------------

# define WR_END 1
# define RE_END 0

typedef struct s_exctx
{
	int		fdin;
	int		fdout;
	bool	is_piped;
	bool	in_subsh;
}	t_exctx;


typedef struct s_excmd
{
	char	**path_arr;
	char	**envp;
	char	*cmd_path;
}	t_excmd;

//Top-level
void		execute_input(t_msh *ms);
bool		is_builtin(char *argv0);
void		walk_ast(t_ast *cur_node, t_exctx ctx, t_msh *ms);
int			interp_waitstat(int wstat);

//Btm-level
bool		run_redirs(t_redir *cur_redir, t_exctx *ctx, t_msh *ms);
void		exc_hdl_cmd(t_ast *cmd_node, t_exctx ctx, t_msh *ms);
void		exc_ext_cmd(char *argv[], t_exctx ctx, t_msh *ms);

//cleanup
void		fd_cls_set(int *fd);
void		fd_cleanup(t_exctx *ctx);

//Error handling
int			ms_perror_stat(char *err_src, int exit_status);

//UTILS -----------------------------------------------------------------------

int			malloc_fail_exit(void);

//MAIN ------------------------------------------------------------------------

typedef struct s_minishell
{
	//ema original
	char		**args;
	t_array		*env;
	bool		shell_exit;

	//juls cont
	t_input		input;

	t_token		*tk_start;
	int			tk_ttl;

	t_ast		*ast_root;
	t_ast		*ast_garbc;

	int			exit_status;
}	t_msh;

#endif
