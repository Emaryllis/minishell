/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:58:22 by julhong           #+#    #+#             */
/*   Updated: 2026/01/29 18:20:17 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static t_ast	*parse_lvl1_pipeline(t_token **cur_tk, t_parse_state *p_state)
{
	t_ast	*pipe_node;
	t_ast	*left;
	t_ast	*right;

	if (!*cur_tk)
	{
		set_pstate_err(p_state);
		p_state->unexp_end = true;
		return (NULL);
	}
	left = parse_lvl0_cmdseg(cur_tk, p_state);
	if (p_state->parse_error || !left)
		return (NULL);
	right = NULL;
	if (*cur_tk && ((*cur_tk)->type == TK_PIPE))
	{
		*cur_tk = (*cur_tk)->next;
		right = parse_lvl1_pipeline(cur_tk, p_state);
	}
	if (p_state->parse_error)
		return (NULL);
	if (right == NULL)
		return (left);
	pipe_node = new_ast_node(AST_PIPE, p_state->garbc_start);
	return (pipe_node->left = left, pipe_node->right = right, pipe_node);
}

static t_ast	*parse_lvl2_logical(t_token **cur_tk, t_parse_state *p_state)
{
	t_ast		*logic_node;
	t_astype	type;
	t_ast		*left;
	t_ast		*right;

	left = parse_lvl1_pipeline(cur_tk, p_state);
	if (p_state->parse_error || !left)
		return (NULL);
	while (*cur_tk && ((*cur_tk)->type == TK_AND || (*cur_tk)->type == TK_OR))
	{
		type = ((*cur_tk)->type == TK_AND) * AST_AND
			+ ((*cur_tk)->type == TK_OR) * AST_OR;
		*cur_tk = (*cur_tk)->next;
		right = parse_lvl1_pipeline(cur_tk, p_state);
		if (p_state->parse_error || !right)
			return (NULL);
		logic_node = new_ast_node(type, p_state->garbc_start);
		logic_node->left = left;
		logic_node->right = right;
		left = logic_node;
	}
	return (left);
}

void	parse_lvl0_subsh(t_token **cur_tk, t_ast *cmd_node,
	t_parse_state *p_state)
{
	cmd_node->type = AST_SUBSH;
	*cur_tk = (*cur_tk)->next;
	if (!*cur_tk || (*cur_tk)->type == TK_SUBSH_CLS)
	{
		if (!*cur_tk)
			p_state->unexp_end = true;
		set_pstate_err(p_state);
		return ;
	}
	cmd_node->left = parse_lvl2_logical(cur_tk, p_state);
	if (p_state->parse_error)
		return ;
	if (!*cur_tk)
	{
		set_pstate_err(p_state);
		p_state->unexp_end = true;
		return ;
	}
	if (*cur_tk && (*cur_tk)->type == TK_SUBSH_CLS)
		*cur_tk = (*cur_tk)->next;
	else
		set_pstate_err(p_state);
}

t_ast	*build_ast(t_msh *ms)
{
	t_parse_state	p_state;

	ft_bzero(&p_state, sizeof(p_state));
	p_state.cur_tk = ms->tk_start;
	p_state.tk_ttl = ms->tk_ttl;
	p_state.garbc_start = &ms->ast_garbc;
	ms->ast_root = parse_lvl2_logical(&p_state.cur_tk, &p_state);
	debug_parse_garbc(*p_state.garbc_start);
	if (!p_state.parse_error && p_state.cur_tk != NULL)
		set_pstate_err(&p_state);
	if (p_state.parse_error)
	{
		pr_syntax_err(p_state);
		return (NULL);
	}
	resolve_hdocs(p_state.hdocs_start, ms);
	if (g_newsig == SIGINT && msh_consume_sigint(ms))
		return (NULL);
	return (ms->ast_root);
}
