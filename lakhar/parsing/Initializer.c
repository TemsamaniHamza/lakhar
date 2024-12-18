#include "../headers/minishell.h"

void    save_input_output(int *fd_input, int *fd_output)
{
    *fd_input = dup(0);
    *fd_output = dup(1);
}

	// s_env	*node_creation_env(char *env, char *var, char *value)
	// {
	// 	s_env	*node;

	// 	node = malloc(sizeof(s_env));
	// 	if (!node)
	// 		exit(1);
	// 	node->env = env;
	// 	node->var = var;
	// 	node->value = value;
	// 	node->next = NULL;
	// 	return (node);
	// }
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
    int i = 0;
    while(env[i])
        i++;
    global.env_copy = malloc((i + 1) * sizeof(char *));
    if(!global.env_copy)
        return;
    i = 0;
    while(env[i])
    {
        global.env_copy[i] = ft_strdup(env[i]);
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