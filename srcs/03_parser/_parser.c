/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:58:22 by julhong           #+#    #+#             */
/*   Updated: 2025/12/04 23:04:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

bool	parenth_bal(char *line)
{
	int	excess_opn;
	int	excess_cls;

	excess_opn = 0;
	excess_cls = 0;
	while (*line)
	{
		if (*line == '(')
			excess_opn++;
		else if (*line == ')')
		{
			if (excess_opn == 0)
				excess_cls++;
			else
				excess_opn--;
		}
		line++;
	}
	if ((excess_opn + excess_cls) == 0)
		return (true);
	return (false);
}

t_ast	*parse_lvl2_logical(t_token **cur_tk, t_msh *msh);

t_ast	*init_basic_cmd(t_ast *cmd_node, t_msh *msh)
{
	cmd_node->type = AST_CMD;
	cmd_node->cmd_av = malloc((msh->tk_ttl + 1) * sizeof(char *));
	if (!cmd_node->cmd_av)
		return (NULL);
	cmd_node->cmd_av[0] = NULL;
	return (cmd_node);
}

bool	addto_cmd_redir(t_token **cur_tk, t_ast *cmd_node)
{
	t_redir	*rdr_node;

	rdr_node = new_redir_node((*cur_tk)->type);
	*cur_tk = (*cur_tk)->next;
	if (*cur_tk)	//handle syntax: expecting TK_WORD
		rdr_node->target = (*cur_tk)->str;
	else
		return (false);
	append_redir(&cmd_node->redir_start, rdr_node);
	*cur_tk = (*cur_tk)->next;
	return (true);
}

void	addto_cmd_words(t_token **cur_tk, t_ast *cmd_node)
{
	cmd_node->cmd_av[cmd_node->cmd_ac] = (*cur_tk)->str;
	cmd_node->cmd_ac++;
	cmd_node->cmd_av[cmd_node->cmd_ac] = NULL;
	*cur_tk = (*cur_tk)->next;
}

t_ast	*parse_lvl0_subsh(t_token **cur_tk, t_msh *msh, t_ast *cmd_node)
{
		cmd_node->type = AST_SUBSH;
		*cur_tk = (*cur_tk)->next;
		cmd_node->left = parse_lvl2_logical(cur_tk, msh);
		*cur_tk = (*cur_tk)->next;
		return (cmd_node);
}

t_ast	*parse_lvl0_cmdseg(t_token **cur_tk, t_msh *msh)
{
	t_ast	*cmd_node;

	cmd_node = new_ast_node(AST_NULL);
	while (*cur_tk && ((*cur_tk)->str[0] == '<' || (*cur_tk)->str[0] == '>'))
			addto_cmd_redir(cur_tk, cmd_node);
	if (*cur_tk && (*cur_tk)->str[0] == '(')
	{
		cmd_node = parse_lvl0_subsh(cur_tk, msh, cmd_node);
		while (*cur_tk && ((*cur_tk)->str[0] == '<' || (*cur_tk)->str[0] == '>'))
			addto_cmd_redir(cur_tk, cmd_node);
		return (cmd_node);
	}
	cmd_node = init_basic_cmd(cmd_node, msh);
	while (*cur_tk)
	{
		if ((*cur_tk)->str[0] == '<' || (*cur_tk)->str[0] == '>')
			addto_cmd_redir(cur_tk, cmd_node);
		else if ((*cur_tk)->type == TK_WORD)
			addto_cmd_words(cur_tk, cmd_node);
		else
			break ;
	}
	return (cmd_node);
}

t_ast	*parse_lvl1_pipeline(t_token **cur_tk, t_msh *msh)
{
	t_ast	*pipe_node;
	t_ast	*left;
	t_ast	*right;

	left = parse_lvl0_cmdseg(cur_tk, msh);
	right = NULL;

	if (*cur_tk && ((*cur_tk)->type == TK_PIPE))
	{
		*cur_tk = (*cur_tk)->next;
		right = parse_lvl1_pipeline(cur_tk, msh);
	}

	if (right == NULL)
		return (left);
	else
	{
		pipe_node = new_ast_node(AST_PIPE);
		pipe_node->left = left;
		pipe_node->right = right;
		return (pipe_node);
	}
}

t_ast	*parse_lvl2_logical(t_token **cur_tk, t_msh *msh)
{
	t_ast		*logic_node;
	t_astype	type;
	t_ast		*left;
	t_ast		*right;

	left = parse_lvl1_pipeline(cur_tk, msh);
	while (*cur_tk && ((*cur_tk)->type == TK_AND || (*cur_tk)->type == TK_OR))
	{
		type = ((*cur_tk)->type == TK_AND) * AST_AND
			+ ((*cur_tk)->type == TK_OR) * AST_OR; 
		*cur_tk = (*cur_tk)->next;
		right = parse_lvl1_pipeline(cur_tk, msh);
		logic_node = new_ast_node(type);
		logic_node->left = left;
		logic_node->right = right;
		left = logic_node;
	}
	return (left);
}

void	build_ast(t_msh *msh)
{
	t_token	*cur_tk;

	cur_tk = msh->tk_start;
	msh->ast_root = parse_lvl2_logical(&cur_tk, msh);
}