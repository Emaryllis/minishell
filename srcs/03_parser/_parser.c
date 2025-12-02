/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:58:22 by julhong           #+#    #+#             */
/*   Updated: 2025/12/02 17:14:03 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

t_ast	*make_cmd_node(t_minsh *msh)
{
	t_ast	*cmd_node;

	cmd_node = new_ast_node(AST_CMD);
	cmd_node->cmd_av = malloc((msh->tk_ttl + 1) * sizeof(char *));
	if (!cmd_node->cmd_av)
		return (NULL);
	cmd_node->cmd_ac = 0;
	cmd_node->cmd_av[0] = NULL;
	return (cmd_node);
}

bool	consume_cmd_redir(t_token **cur_tk, t_ast *cmd_node)
{
	t_redir	*rdr_node;

	rdr_node = new_redir_node((*cur_tk)->type);
	*cur_tk = (*cur_tk)->next;
	if (*cur_tk)
		rdr_node->target = (*cur_tk)->str;
	else
		return (false);
	append_redir(&cmd_node->redir_start, rdr_node);
	*cur_tk = (*cur_tk)->next;
	return (true);
}

void	consume_cmd_word(t_token **cur_tk, t_ast *cmd_node)
{
	cmd_node->cmd_av[cmd_node->cmd_ac] = (*cur_tk)->str;
	cmd_node->cmd_ac++;
	cmd_node->cmd_av[cmd_node->cmd_ac] = NULL;
	*cur_tk = (*cur_tk)->next;
}

t_ast	*parse_cmdseg(t_token **cur_tk, t_minsh *msh)
{
	t_ast	*cmd_node;

	cmd_node = make_cmd_node(msh);
	while (*cur_tk)
	{
		if ((*cur_tk)->str[0] == '<' || (*cur_tk)->str[0] == '>')
			consume_cmd_redir(cur_tk, cmd_node);
		else if ((*cur_tk)->type == TK_WORD)
			consume_cmd_word(cur_tk, cmd_node);
		else
			break ;
	}
	return (cmd_node);
}

t_ast	*recur_parse_pipeline(t_token **cur_tk, t_minsh *msh)
{
	t_ast	*left;
	t_ast	*pipe;
	t_ast	*right;

	left = parse_cmdseg(cur_tk, msh);
	right = NULL;

	if (*cur_tk && ((*cur_tk)->type == TK_PIPE))
	{
		*cur_tk = (*cur_tk)->next;
		right = recur_parse_pipeline(cur_tk, msh);
	}

	if (right == NULL)
		return (left);
	else
	{
		pipe = new_ast_node(AST_PIPE);
		pipe->cmd_left = left;
		pipe->cmd_right = right;
		return (pipe);
	}
}

void	build_ast(t_minsh *msh)
{
	t_token	*cur_tk;

	cur_tk = msh->tk_start;
	msh->ast_root = recur_parse_pipeline(&cur_tk, msh);
}