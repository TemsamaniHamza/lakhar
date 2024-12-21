#include "../headers/minishell.h"

int	check_not_operator(s_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (1);
	else
		return (0);
}

int	check_rpr(char *s, int i)
{

    while (s[i] != '\0')
    {
        if (s[i] == ')')
            return (i);
        i++;
    }
    printf("syntax error: unclosed parentheses");
    global.exited = 258;
    return (-1);
}

int	check_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	check_syntax_help(s_token tok, s_token next)
{
	if (tok == OR || tok == AND || tok == PIPE)
	{
		if (next == STR || next == IN || next == OUT
			|| next == APPEND || next == LPR)
			return (1);
	}
	if (tok == LPR)
	{
		if (next == STR || next == IN || next == OUT
			|| next == APPEND || next == LPR)
			return (1);
	}
	if (tok == RPR)
	{
		if (next == AND || next == OR || next == PIPE
			|| next == RPR || next == END)
			return (1);
	}
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
	{
		if (next == STR)
			return (1);
	}
	return (0);
}

int	check_syntax_error(s_token tok, char *s)
{
	s_token	next;

	next = return_token(*s, *(s + 1));
	if (check_syntax_help(tok, next))
		return (1);
	if (next == END)
    {
		printf("syntax error near unexpected token`newline'\n");
        global.exited = 258;
    }
	else if (next == AND || next == OR || next == APPEND || next == HEREDOC)
    {
		printf("syntax error near unexpected token`%c%c'\n", *s, *(s + 1));
        global.exited = 258;
    }
	else
    {
		printf("syntax error near unexpected token`%c'\n",*s);
        global.exited = 258;
    }
	return (0);
}

int return_token_syntax(int tok,char *s, int *i,  int *par)
{
    (*i)++;
    if (tok == OR || tok == AND || tok == HEREDOC || tok == APPEND)
		(*i)++;
    else if(tok == LPR)
    {
        if(*par == 0)
            *par = *i;
        *par = check_rpr(&s[*par], *par) + 1;
        if (*par == 0)
            return (0);
    }
    else if (tok == RPR && *i > *par)
    {
        printf("syntax error: unexpected ')'");
        global.exited = 258;
        return (0);
    }
	while (check_spaces(s[*i]) == 1)
		(*i)++;
    if(!check_syntax_error(tok, &s[*i]))
        return(0);
    return(1);
}
s_input	*creat_node_command(char *s, s_redir *redir, s_token tok, int token_flag)
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
int	build_command_list(s_input **head, s_input *add)
{
	s_input	*help;

	if (!head || !add)
		return (0);
	if (!*head)
		*head = add;
	else
	{
		help = *head;
		while(help->right)
			help = help->right;
		help->right = add;
		add->left = help;
	}
	return (1);
}

int	check_command(s_token tok)
{
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (4);
	if (tok == PIPE)
		return (3);
	if (tok == OR || tok == AND)
		return (2);
	return (1);
}
int token_1(s_input **head, char *s, int *i, int *par)
{
    s_token tok;
    s_input *new;

    tok = return_token(s[*i], s[(*i) + 1]);
    if(check_not_operator(tok) == 0)
    {
        if(return_token_syntax(tok,s,i,par) == 0)
            return(0);
		new = creat_node_command(NULL, NULL, tok,check_command(tok));
    }
	else
		new = token_2(s,i,tok);
	if (!new)
		return (0);
	if (new->tok == LPR)
	{
		if(new->tok == LPR)
			return(free(new),0);
	}
	build_command_list(head, new);
	return (1);
}