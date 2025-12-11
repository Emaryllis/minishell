/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdseg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:35:21 by julhong           #+#    #+#             */
/*   Updated: 2025/12/11 21:54:05 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	init_basic_cmd(t_ast *cmd_node, t_parse_state *p_state)
{
	if (p_state->parse_error)
		return ;
	cmd_node->type = AST_CMD;
	cmd_node->cmd_av = malloc((p_state->tk_ttl + 1) * sizeof(char *));
	if (!cmd_node->cmd_av)
		malloc_fail_exit();
	cmd_node->cmd_av[0] = NULL;
}

static void	add_next_word(t_token **cur_tk, t_ast *cmd_node)
{
	cmd_node->cmd_av[cmd_node->cmd_ac] = (*cur_tk)->str;
	cmd_node->cmd_ac++;
	cmd_node->cmd_av[cmd_node->cmd_ac] = NULL;
	*cur_tk = (*cur_tk)->next;
}

static void	consume_redirs(t_token **cur_tk, t_ast *cmd_node,
	t_parse_state *p_state)
{
	t_redir		*rdr_node;
	t_toktype	rdr_type;

	while (*cur_tk
		&& ((*cur_tk)->type >= TK_RDR_IN && (*cur_tk)->type <= TK_RDR_APND))
	{
		rdr_type = (*cur_tk)->type;
		*cur_tk = (*cur_tk)->next;
		if (*cur_tk && (*cur_tk)->type == TK_WORD)
		{
			rdr_node = new_redir_node(rdr_type);
			rdr_node->target = (*cur_tk)->str;
			append_redir(&cmd_node->redir_start, rdr_node);
			*cur_tk = (*cur_tk)->next;
			continue ;
		}
		set_pstate_err(p_state);
		return ;
	}
}

static void	parse_lvl0_subsh(t_token **cur_tk, t_ast *cmd_node,
	t_parse_state *p_state)
{
	cmd_node->type = AST_SUBSH;
	*cur_tk = (*cur_tk)->next;
	cmd_node->left = parse_lvl2_logical(cur_tk, p_state);
	*cur_tk = (*cur_tk)->next; //check for subshell syntax
}

t_ast	*parse_lvl0_cmdseg(t_token **cur_tk, t_parse_state *p_state)
{
	t_ast	*cmd_node;

	if (p_state->parse_error)
		return (NULL);
	cmd_node = new_ast_node(AST_NULL);
	consume_redirs(cur_tk, cmd_node, p_state);
	if (*cur_tk && ((*cur_tk)->type == TK_SUBSH_OPN))
	{
		parse_lvl0_subsh(cur_tk, cmd_node, p_state);
		consume_redirs(cur_tk, cmd_node, p_state);
		return (cmd_node);
	}
	init_basic_cmd(cmd_node, p_state);
	while (*cur_tk)
	{
		if (*cur_tk && (*cur_tk)->type == TK_WORD)
			add_next_word(cur_tk, cmd_node);
		else if ((*cur_tk)->type >= TK_RDR_IN && (*cur_tk)->type <= TK_RDR_APND)
			consume_redirs(cur_tk, cmd_node, p_state);
		else
			break ;
	}
	return (cmd_node);
}
