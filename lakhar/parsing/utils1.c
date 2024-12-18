#include "../headers/minishell.h"

s_token	return_token(char c1, char c2)
{
	if (c1 == '|' && c2 == '|')
	{
		printf("the c2 dzb is :%c\n", c2);
		return (OR);
	}
	else if (c1 == '&' && c2 == '&')
	{
		printf("the c2 dzb is : %c\n", c2);
		return (AND);
	}
	else if (c1 == '<' && c2 == '<')
		return (HEREDOC);
	else if (c1 == '>' && c2 == '>')
		return (APPEND);
	else if (c1 == '(')
		return (LPR);
	else if (c1 == ')')
		return (RPR);
	else if (c1 == '|')
		return (PIPE);
	else if (c1 == '>')
		return (OUT);
	else if (c1 == '<')
		return (IN);
	else if (!c1)
		return (END);
	else
		return (STR);
}

s_input	*node_creation_cmd(char *s, s_redir *redir, s_token tok, int token_flag)
{
	s_input	*node;

	node = malloc(sizeof(s_input));
	if (!node)
		exit(1);
	node->command = s;
	node->cmd = NULL;
	node->tok = tok;
	node->token_flag = token_flag;
	node->redirections = redir;
	node->left = NULL;
	node->right = NULL;
	return (node);
}