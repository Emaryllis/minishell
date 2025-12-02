/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:49:02 by julhong           #+#    #+#             */
/*   Updated: 2025/12/02 22:59:42 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINSH_H
# define MINSH_H

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

//Includes: OTHERS ----------------------//
# include <stdbool.h>
# include <errno.h>
# include "libft.h"

//Forward Declarations --------------------------------------------------------

typedef struct s_token	t_token;
typedef struct s_ast	t_ast;
typedef struct s_redir	t_redir;

//MAIN ------------------------------------------------------------------------

typedef struct s_minsh
{
	char	*line;

	t_token	*tk_start;
	int		tk_ttl;

	t_ast	*ast_root;
}	t_minsh;

//LEXER -----------------------------------------------------------------------

typedef enum e_toktype
{
	TK_WORD,
	TK_RDR_IN,
	TK_RDR_HERE,
	TK_RDR_OUT,
	TK_RDR_APND,
	TK_SUBSH,
	TK_PIPE,
	TK_AND,
	TK_OR
}	t_toktype;

typedef struct s_token //FREE token node
{
	char		*str; //FREE string LATER (will be reused in AST)
	t_toktype	type;
	t_token		*next;
}	t_token;

bool	lex_tokens(t_minsh *minsh, char *cur);

//Nodes
t_token	*new_token(char *src, int len, t_toktype type);
void	append_token(t_token **start, t_token *new);
void	clear_tokens(t_token **start);

//Utils
bool	all_isspace(const char *str);
void	adv_ptr_isspace(char **cur);
void	adv_indx_quote(char *start, int *i, char quote);

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

typedef struct s_redir //FREE redir node
{
	t_toktype	type;
	char		*target;	//reuse strings from lexer
	t_redir		*next;
}	t_redir;

typedef struct s_ast
{
	t_astype	type;
	t_ast		*left;
	t_ast		*right;

	//CMD Segment
	int			cmd_ac;
	char		**cmd_av;	//FREE outer (but reuse strings from lexer)
	t_redir		*redir_start;

}	t_ast;

void	build_ast(t_minsh *msh);
void	print_ast(t_ast *node, int depth);

//Nodes
t_ast	*new_ast_node(t_astype type);
t_redir	*new_redir_node(t_toktype type);
void	append_redir(t_redir **start, t_redir *new);


#endif
