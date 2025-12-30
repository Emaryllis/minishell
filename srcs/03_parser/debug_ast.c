/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEMP_printast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:04:01 by julhong           #+#    #+#             */
/*   Updated: 2025/12/30 15:34:50 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	print_indent(int depth)
{
	int	i;

	i = -1;
	while (++i < depth)
		printf("    ");
}

static void	print_redirs(t_redir *r, int depth)
{
	while (r)
	{
		print_indent(depth);
		printf("  redir: type=%d target=%s\n", r->type, r->target);
		r = r->next;
	}
}

static void	print_ast_cmd(t_ast *node, int depth)
{
	int	i;

	print_indent(depth);
	printf("  argv:");
	i = -1;
	while (++i < node->cmd_ac)
		printf(" %s", node->cmd_av[i]);
	printf("\n");
	if (node->redir_start)
	{
		print_indent(depth);
		printf("  redirs:\n");
		print_redirs(node->redir_start, depth + 1);
	}
}

static void	print_ast_subsh(t_ast *node, int depth)
{
	if (node->redir_start)
	{
		print_indent(depth);
		printf("  redirs:\n");
		print_redirs(node->redir_start, depth + 1);
	}
	print_indent(depth);
	printf("  (subshell-body):\n");
	print_ast(node->left, depth + 1);
}

void	print_ast(t_ast *node, int depth)
{
	if (!DEBUG || !node)
		return ;
	print_indent(depth);
	printf("[%s]\n", get_ast_type(node->type));
	if (node->type == AST_CMD)
		return (print_ast_cmd(node, depth));
	if (node->type == AST_SUBSH)
		return (print_ast_subsh(node, depth));
	print_indent(depth);
	printf("  left:\n");
	print_ast(node->left, depth + 1);
	print_indent(depth);
	printf("  right:\n");
	print_ast(node->right, depth + 1);
}
