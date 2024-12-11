#include "../headers/minishell.h"

void ft_execute(s_input *input)
{
    if(!input)
        return;
    // else if(input->tok == AND)
    //     return(exec_and(input));
    // else if(input->tok == OR)
    //     return(exec_or(input));
    // else if(input->tok == PIPE)
    //     return(exec_pipe(input));
    if(input->tok == STR)
        return(exec_str(input));
        
}

void exec_str(s_input *input)
{
    // check about expand and redirection case

    input->cmd = expand(input->command);
}

char **expand(char *command)
{
    char **cmd;
    cmd = parsing_cmd(command);

    return(cmd);
}
int find_len(char *str)
{
    int i;
    int ret;
                // implement the expand cases next
    i = 0;
    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i] == 39)
        {
            ret += look_for_1_quote(str, &i, str[i]);

        }
        else if(str[i] == 34)
            ret += look_for_1_quote(str, &i, str[i]);
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
    i = 0;
    return(return_cmd);
}