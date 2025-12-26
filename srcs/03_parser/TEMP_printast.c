#include "minsh.h"

void	print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("    ");  // 4 spaces per indent
}

void	print_redirs(t_redir *r, int depth)
{
	while (r)
	{
		print_indent(depth);
		printf("  redir: type=%d target=%s\n", r->type, r->target);
		r = r->next;
	}
}

const char	*ast_type_str(t_astype type)
{
	if (type == AST_CMD)    return "CMD";
	if (type == AST_PIPE)   return "PIPE";
	if (type == AST_AND)    return "AND";
	if (type == AST_OR)     return "OR";
	if (type == AST_SUBSH)  return "SUBSHELL";
	return "NULL";
}

void	print_ast(t_ast *node, int depth)
{
	if (!DEBUG)
		return ;
	if (!node)
	{
		print_indent(depth);
		printf("(null)\n");
		return ;
	}

	print_indent(depth);
	printf("[%s]\n", ast_type_str(node->type));

	// ─────────────────────────────────────────
	//                      CMD
	// ─────────────────────────────────────────
	if (node->type == AST_CMD)
	{
		print_indent(depth);
		printf("  argv:");
		for (int i = 0; i < node->cmd_ac; i++)
			printf(" %s", node->cmd_av[i]);
		printf("\n");

		if (node->redir_start)
		{
			print_indent(depth);
			printf("  redirs:\n");
			print_redirs(node->redir_start, depth + 1);
		}
		return ;
	}

	// ─────────────────────────────────────────
	//                  SUBSHELL
	// ─────────────────────────────────────────
	if (node->type == AST_SUBSH)
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
		return ;
	}


	// ─────────────────────────────────────────
	//         PIPE / AND / OR (binary ops)
	// ─────────────────────────────────────────
	print_indent(depth);
	printf("  left:\n");
	print_ast(node->left, depth + 1);

	print_indent(depth);
	printf("  right:\n");
	print_ast(node->right, depth + 1);
}
