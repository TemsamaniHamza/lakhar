#include "../headers/minishell.h"

void ft_execute(s_input *input)
{
    if(!input)
        return;
    else if(input->tok == OR)
        return(exec_and(input));
    // else if(input->tok == OR)
    //     return(exec_or(input));
    // else if(input->tok == PIPE)
    //     return(exec_pipe(input));
    if(input->tok == STR)
        return(exec_str(input));
        
}

void exec_and(s_input *input)
{
    // printf("%d", input->tok);
    ft_execute(input->left);
    if(global.exited == 0)
        ft_execute(input->right);
}
void    fill_between_quote_1(char **str, char *s, int *i)
{
	while (s[*i])
	{
		*(*str)++ = s[(*i)++];
		if (s[*i] == 39)
		{
			*(*str)++ = s[(*i)++];
			*(*str) = '\0';
			return ;
		}
	}
}

void	change_val(char **keep, char *s, int *i)
{
	char	*var;
	char	**ret;
	char	*save;
	int	    flg;

	(*i)++;
	ret = keep;
	flg = 0;
	if (s[*i] == '?')
		flg = 1;
	var = expand_var(s, i);
	save = var;
	if (!var)
		return ;
	while (*var)
		*(*ret)++ = *var++;
	*(*ret) = '\0';
	if (flg)
		free(save);
}
void    ft_change_command(char *command, char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == 39)
            fill_between_quote_1(&command, str, &i);
        else if(str[i] == 34)
            fill_between_quote_2(&command, str, &i);
        else if(str[i] == '$' && (is_legit(str[i + 1]) || str[i + 1] == '?'))
            change_val(&command, str, &i);
        else if(str[i] == '$' && (str[i + 1] == 34 || str[i + 1] == 39))
            i++;
        else
            *command++ = str[i++];
    }
    *command = '\0';
}
void	fill_between_quote_2_help(char **str, int *i, char *s)
{
	char	*var;

	(*i)++;
	var = expand_var(s, i);
	if (!var || !*var)
		return ;
	while (*var)
		*(*str)++ = *var++;
}
void   fill_between_quote_2(char **str, char *s, int *i)
{
	*(*str)++ = s[(*i)++];
	while (s[*i])
	{
		if (s[*i] == '$' && is_legit(s[(*i) + 1]))
			fill_between_quote_2_help(str, i, s);
		else if (s[*i] == 34)
		{
			*(*str)++ = s[(*i)++];
			*(*str) = '\0';
			return ;
		}
		else
			*(*str)++ = s[(*i)++];
		*(*str) = '\0';
	}
}
// char *parsing_redirection(s_redir *redir, char *str ,int *flag)
// {
//     int j;
//     char *command;
//     int i;

//     i = 0;
//     if(redir->tok != HEREDOC)
//     {
//         j = find_len(str); 
//         if (j < 0)
//             return (NULL);
//         command = malloc(sizeof(char) * (j + 1));
//         if (!command)
//             return (NULL);
//         ft_change_command(command, str);
//     }
// }

void exec_str(s_input *input)
{
    int status;
    char *path;

    input->cmd = parsing_cmd(input->command);
    if(!input->cmd)
        return ;
	if (input->cmd && !input->cmd[0])
		(free(input->cmd), input->cmd = NULL);
	if (input->cmd && input->cmd[0] && !builtins(input->cmd))
	{
        // find path execute child exit with status blablabla
        //free path
        return ;
	}
}

int    expand(s_input *input)
{
    int flag;
    s_redir *redir;
    input->cmd = parsing_cmd(input->command);
    if(!input->cmd)
        return(0);
    input->command = NULL;
    // redir = input->redirections;
    // if(redir)
    // {
    //     while(redir)
    //     {
    //         redir->file = parsing_redirection(redir, redir->file, &flag);
    //         if (!redir->file[0])
    //         {
	// 			ft_putstr_fd("bash: ambiguous redirect\n", 2);
	// 			global.exited = 0;
    //         }
	// 		if (!redir->file)
	// 			return (0);
	// 		redir->flag = flag;
	// 		redir = redir->right;
    //     }
    // }
    return(1);
}

int is_legit(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return 1;
    else if (c >= '0' && c <= '9')
        return 1; 
    else
        return 0;
}

// char *ft_getenv(char *s)
// {
//     int i;

//     if(!global.env || !s)
//         return(NULL);
//     i = 0;
//     env = global.env;
//     while(env)
//     {
//         if(!ft_memcmp(s, env->var, ft_strlen(s) + 1))
//             return(env->value);
//         env = global.env;
//     }
//     return(NULL);
// }

char *expand_var(char *str, int *i)
{
    int save;
    char *v;
    char *s;

    save = *i;
    if (s[save] == '?')
    {
        (*i)++;
        ft_itoa(global.exited);
    }
    while (is_legit(s[save]))
        save++;
    save -= *i;
    s = ft_substr(str, *i, save);
    // v = ft_getenv(s);
    *i += save;
    // if (!v)
    // {
    //     free(s);
    //     return (NULL);
    // }
    free(s);
    return (v);
}

int length_val(char *str, int *i)
{
    char *val;
    int flag;
    int len;

    (*i)++;
    flag = 0;
    if(str[*i] == '?')
        flag = 1;
    val = expand_var(str,i); // check
    if(!val)
        return (0);
    if (flag)
        free(val);
    return (len);   
}
int find_len(char *str)
{
    int i;
    int ret;
                // implement the expand cases next
    ret = 0;
    i = 0;

    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i] == 39)
            ret += look_for_1_quote(str, &i, str[i]);
        else if(str[i] == 34)
            ret += look_for_1_quote(str, &i, str[i]);
        else if (str[i] == '$' && (is_legit(str[i + 1]) || str[i + 1] == '?'))
            ret += length_val(str, &i);
        else if(str[i] == '$' && (str[i + 1] == 34 || str[i + 1] == 39))
            i++;
        else
        {
            i++;
            ret++;
        }
    }
    return(ret);
}
int look_for_1_quote(char *str, int *i, char c)
{
    int ret;

    ret = 0;
    while(str[*i])
    {
        (*i)++;
        ret++;
        if(str[*i] == c)
        {
            (*i)++;
            ret++;
            return(ret);
        }
    }
    return(-1);
}
char **parsing_cmd(char *str)
{
    int len;
    char *cmd;
    int i ;
    char **return_cmd;

    len = 0;
    i = 0;
    len = find_len(str);
    if(len<0)
        return(NULL);
    cmd = malloc(sizeof(char) * (len + 1));
    if(!cmd)
        return(NULL);
    return_cmd = fill_command(str, len, &i, 0);
    delete_quotes(return_cmd);
    return(return_cmd);
}

void	delete_quotes(char **args)
{
	char	*str;
    
	while (*args)
	{
		str = new_cmd(*args, NULL);
		*args = str;
		args++;
	}
}

char	*new_cmd(char *s, int *flg)
{
	char	*new;
	char	*save;
	int	l;
	char	keep;

	new = malloc(sizeof(char) * (calc_len(s) + 1));
	if (!new)
		exit(1);
	l = 0;
	save = s;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			keep = *s++;
			should_expnd(flg);
			while (*s != keep)
				new[l++] = *s++;
			s++;
			continue ;
		}
		new[l++] = *s++;
	}
	return (new[l] = '\0', free(save), new);
}

int	calc_len(char *s)
{
	int	    l;
	int	    save;
	char	keep;

	l = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			keep = *s;
			save = check_next_quote(s++, keep);
			s += save + 1;
			l += save;
		}
        else
        {
		    s++;
		    l++;
        }
	}
	return (l);
}

void	should_expnd(int *flg)
{
	if (flg)
		*flg = 0;
}