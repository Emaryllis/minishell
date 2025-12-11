/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:58:22 by julhong           #+#    #+#             */
/*   Updated: 2025/12/11 12:54:26 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// static bool	parenth_bal(char *line)
// {
// 	int	excess_opn;
// 	int	excess_cls;

// 	excess_opn = 0;
// 	excess_cls = 0;
// 	while (*line)
// 	{
// 		if (*line == '(')
// 			excess_opn++;
// 		else if (*line == ')')
// 		{
// 			if (excess_opn == 0)
// 				excess_cls++;
// 			else
// 				excess_opn--;
// 		}
// 		line++;
// 	}
// 	if ((excess_opn + excess_cls) == 0)
// 		return (true);
// 	return (false);
// }

static t_ast	*parse_lvl1_pipeline(t_token **cur_tk, t_msh *msh)
{
	t_ast	*pipe_node;
	t_ast	*left;
	t_ast	*right;

	left = parse_lvl0_cmdseg(cur_tk, msh);
	if (!left)
		return (NULL);
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
	if (!left)
		return (NULL);
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
