#include "../headers/minishell.h"

s_token	return_token(char c1, char c2)
{
	if (c1 == '|' && c2 == '|')
	{
		return (OR);
	}
	if (c1 == '&' && c2 == '&')
	{
		return (AND);
	}
	if (c1 == '<' && c2 == '<')
		return (HEREDOC);
	if (c1 == '>' && c2 == '>')
		return (APPEND);
	if (c1 == '(')
		return (LPR);
	if (c1 == ')')
		return (RPR);
	if (c1 == '|')
		return (PIPE);
	if (c1 == '>')
		return (OUT);
	if (c1 == '<')
		return (IN);
	if (!c1)
		return (END);
	else
		return (STR);
}

s_input	*node_creation_cmd(char *s, s_redir *redir, s_token tok, int token_flag)
{
	s_input	*node;

	node = malloc(sizeof(s_input));
	if (!node)
	{
		printf("failes\n");
		exit(1);
	}
	node->command = s;
	node->cmd = NULL;
	node->tok = tok;
	node->token_flag = token_flag;
	node->redirections = redir;
	node->left = NULL;
	node->right = NULL;
	return (node);
}