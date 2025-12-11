/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdseg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:35:21 by julhong           #+#    #+#             */
/*   Updated: 2025/12/11 14:15:27 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// static bool	addto_cmd_redir(t_msh *msh, t_token **cur_tk, t_ast *cmd_node)
// {
// 	t_redir	*rdr_node;

// 	*cur_tk = (*cur_tk)->next;
// 	if (*cur_tk && (*cur_tk)->type == TK_WORD)	//handle syntax: expecting TK_WORD
// 	{
// 		rdr_node = new_redir_node((*cur_tk)->type);
// 		rdr_node->target = (*cur_tk)->str;
// 		append_redir(&cmd_node->redir_start, rdr_node);
// 		*cur_tk = (*cur_tk)->next;
// 		return (true);
// 	}
// 	msh->exit_status = parse_err_syntax(*cur_tk);
// 	return (false);
// }

static t_ast	*init_basic_cmd(t_ast *cmd_node, t_msh *msh)
{
	cmd_node->type = AST_CMD;
	cmd_node->cmd_av = malloc((msh->tk_ttl + 1) * sizeof(char *));
	if (!cmd_node->cmd_av)
		return (NULL);
	cmd_node->cmd_av[0] = NULL;
	return (cmd_node);
}

static bool	consume_redirs(t_token **cur_tk, t_ast *cmd_node, t_msh *msh)
{
	t_redir	*rdr_node;
	
	while (*cur_tk
		&& ((*cur_tk)->type >= TK_RDR_IN && (*cur_tk)->type <= TK_RDR_OUT))
	{
		*cur_tk = (*cur_tk)->next;
		if (*cur_tk && (*cur_tk)->type == TK_WORD)
		{
			rdr_node = new_redir_node((*cur_tk)->type);
			rdr_node->target = (*cur_tk)->str;
			append_redir(&cmd_node->redir_start, rdr_node);
			*cur_tk = (*cur_tk)->next;
			continue ;
		}
		msh->exit_status = parse_err_syntax(*cur_tk);
		return (false);
	}
	return (true);
}

static void	addto_cmd_words(t_token **cur_tk, t_ast *cmd_node)
{
	cmd_node->cmd_av[cmd_node->cmd_ac] = (*cur_tk)->str;
	cmd_node->cmd_ac++;
	cmd_node->cmd_av[cmd_node->cmd_ac] = NULL;
	*cur_tk = (*cur_tk)->next;
}

static t_ast	*parse_lvl0_subsh(t_token **cur_tk, t_msh *msh, t_ast *cmd_node)
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
	if (!consume_redirs(cur_tk, cmd_node, msh))
		return (NULL);
	if (*cur_tk && ((*cur_tk)->type == TK_SUBSH_OPN))
	{
		cmd_node = parse_lvl0_subsh(cur_tk, msh, cmd_node);
		if (!consume_redirs(cur_tk, cmd_node, msh))
			return (NULL);
		return (cmd_node);
	}
	cmd_node = init_basic_cmd(cmd_node, msh);
	while (*cur_tk && ((*cur_tk)->type == TK_WORD 
		|| ((*cur_tk)->type >= TK_RDR_IN && (*cur_tk)->type <= TK_RDR_OUT)))
	{
		if (!consume_redirs(cur_tk, cmd_node, msh))
			return (NULL);
		if (*cur_tk && (*cur_tk)->type == TK_WORD)
			addto_cmd_words(cur_tk, cmd_node);
	}
	return (cmd_node);
}
