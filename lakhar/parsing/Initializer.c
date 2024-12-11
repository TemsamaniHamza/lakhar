#include "../headers/minishell.h"

void    save_input_output(int *fd_input, int *fd_output)
{
    *fd_input = dup(0);
    *fd_output = dup(1);
}

void ft_initialize_env(char **env)
{
    int i; 
    i = 0;
    while(env[i])
        i++;
    global.env = malloc(sizeof(char *) * (i + 1));
    if(!global.env)
        return;
    i = 0;
    while(env[i])
    {
        global.env[i] = ft_strdup(env[i]);
        i++;
    }
}

void    ft_initialize(char **env, int *fd_input, int *fd_output)
{
    global.executed = 0;
    global.exited = 0;
    save_input_output(fd_input, fd_output);
    if(global.exited == 0)
        ft_initialize_env(env);
}