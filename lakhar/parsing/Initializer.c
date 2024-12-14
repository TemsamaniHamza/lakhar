#include "../headers/minishell.h"

void    save_input_output(int *fd_input, int *fd_output)
{
    *fd_input = dup(0);
    *fd_output = dup(1);
}

s_env	*node_creation_env(char *env, char *var, char *value)
{
	s_env	*node;

	node = malloc(sizeof(s_env));
	if (!node)
		exit(1);
	node->env = env;
	node->var = var;
	node->value = value;
	node->next = NULL;
	return (node);
}
int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}


void ft_initialize_env(char **env)
{
    int i; 

    i = 0;
    if(!env)
        return;
    while(env[i])
        i++;

    while(env[i])
    {
        i = find_char(*env, '=');
        ft_lstadd_back(&global.env, node_creation_env(ft_strdup(*env),
				ft_substr(*env, 0, i), ft_substr(*env, i + 1,
					ft_strlen(*env) - i)));
        if(global.exited)
            return; // free env
        env++;
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