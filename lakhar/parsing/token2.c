#include "../headers/minishell.h"

int	check_true(s_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (1);
	else
		return (0);
}

int build_redir_list(s_redir **head, s_redir *add)
{
	s_redir *plus;

	if(!head || !add)
		return (0);
	if (!*head)
		*head = add;
	else
	{
		plus = *head;
		while (plus->right)
			plus = plus->right;
		plus->right = add;
		add->left = plus;
	}
	return (1);
}
int	check_syntax(s_token tok, char *s)
{
	s_token	check;

	// printf(" %s\n", s);
	// printf("[%c] and [%c]\n", *s--, *(s + 1));
	// exit(1);
	check = return_token(*s, *(s + 1));
	// printf(">>>> check is %d <<<<\n", check);
	// printf("%d\n", check);
	// printf("%c ---> %c ----> %c\n", *(s--), *s, *(s + 1));
	if (check_syntax_help(tok, check) == 1)
		return (1);
	if (check == END)
	{
        printf("bash: syntax error near unexpected token `newline'\n");
		global.exited = 258;
    }
	else if (check == AND || check == OR || check == APPEND || check == HEREDOC)
    {
		printf("bash: syntax error near unexpected token `%c%c'\n", *s, *(s + 1));
		global.exited = 258;
    }
	else
	{
		// printf("%d\n", check);
		printf("bash: syntax error near unexpected token `%c'\n", *s);
		// exit(1);
		global.exited = 258;;
	}
	return (0);
}

int check_next_quote(char *s, char c)
{
	int i;

	i = 0;
	while(*s)
	{
		if (*s == c)
			return(i);
		i++;
		s++;
	}
	printf("syntax error: unclosed quotes");
	return -1;
}

void check_flag(int flag, char *s, int *k)
{
	if(!flag)
		s[(*k) - 1] = 127;
}
char	*cmd_help(char *s, int l, int *k, int flag)
{
	int	i;
	int	j;
	char	*ret;

	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
	{
		printf("failes\n");
		exit(1);
	}
	i = 0;
	while (i < l)
	{
		if (s[*k] == 34 || s[*k] == 39)
		{
			j = check_next_quote(&s[(*k) + 1], s[*k]) + i + 1;
			while (i < j)
			{
				ret[i++] = s[(*k)++];
				check_flag(flag, s, k);
			}
		}
		if (s[*k] == 32)
			s[*k] = 127;
		ret[i++] = s[(*k)++];
		check_flag(flag, s, k);
	}
	return (ret[i] = 0, ret);
}

char **fill_command(char *s, int l, int *k, int flag)
{
	char *prep;
	char **freturn;

	if(l<0)
		return(NULL);
	prep = cmd_help(s, l, k, flag);
	freturn = ft_split(prep, 127);
	free(prep);
	prep = NULL;
	return (freturn);
}

char **prep_cmd(char *s, int *i, int flag, s_token tok)
{
	char **freturn;
	s[*i] = 127;
	(*i)++;
	if(tok == HEREDOC || tok == APPEND)
	{
		s[*i] = 127;
		(*i)++;
	}

	while(check_spaces(s[*i]) == 1)
		(*i)++;
	if(check_syntax(tok, (s + *i)) == 0)
		return NULL;
	freturn = fill_command(s, str_len(s, *i, flag), i, flag);
	return (freturn);
}

int	choose_str(char c, int flag)
{

	if ((flag && return_token(c, 0) == STR) || (!flag && return_token(c, 0) == STR && !check_spaces(c)))
		return (1);
	else
		return (0);
}
int str_len(char *s, int i, int flag)
{
	int l;
	int keep;

	l = 0;
	while(s[i] && choose_str(s[i], flag))
	{
		if(s[i] == 34 || s[i] == 39)
		{
			keep = check_next_quote(&s[i + 1], s[i]);
			if (keep == -1)
				return (-1);
			l += keep + 1;
			i += keep + 1;
		}
		l++;
		i++;
	}
	if (!flag)
	{
		while (check_spaces(s[i++]))
			l++;
	}
	return (l);
}

void	incre(char *s, int *i)
{
	ssize_t	l;

	l = str_len(s, *i, 1);
	while (l--)
    	(*i)++;
}
s_redir	*node_create_redirection(char **s, s_token tok)
{
	s_redir	*node;

	if (!s)
		return (NULL);
	node = malloc(sizeof(s_redir));
	if (!node)
	{
		printf("failes\n");
		exit(1);
	}
	node->tok = tok;
	node->file = s[0];
	node->flag = 1;
	node->left = NULL;
	node->right = NULL;
	free(s);
	s = NULL;
	return (node);
}

s_input	*token_2(char *s ,int *i ,s_token tok)
{
    int save;
	char *str;
	s_redir *redir;
	int j = 0;
	save = *i;
	redir = NULL;
	// printf("%d\n", tok);
	// exit(1);
	while(check_true(tok) == 1)
	{
		if (tok != STR)
		{
			if(!build_redir_list(&redir,node_create_redirection(prep_cmd(s, &save, 0, tok), tok)))
				return(0);
		}
		else
			save++;
		tok = return_token(s[save], s[save + 1]);
		j++;
	}
	save = str_len(s, *i, 1);
	if(save<0)
		return (NULL);
	str = ft_substr(s, *i, save);
	if(!str)
		return (NULL);
	incre(s, i);
	return (node_creation_cmd(str,redir,STR, 0));
}
