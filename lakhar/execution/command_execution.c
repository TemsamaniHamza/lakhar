/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:39:32 by rboulaga          #+#    #+#             */
/*   Updated: 2024/11/19 21:41:08 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void    free_list(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int     help(char **cmd)
{
    char **test;    
    char *tmp;
    int i;

    tmp = global.path;
    i = 0;
    while (*tmp != '=')
        tmp++;
    tmp++;
    if (*tmp)
    {
        test = ft_split(tmp, ':');
        while (test[i])
        {
            free(global.path);
            tmp = ft_strjoin(test[i], "/");
            global.path = ft_strjoin(tmp, cmd[0]);
            if (access(global.path, X_OK) == 0)
                return(free_list(test), 1);
            i++;
        }
    }
    return (global.wall = 1, 0);
}

int     find_path(char **cmd)
{
    int i;
    
    i = 0;
    while (global.env_copy[i])
    {
        if (ft_ncmp("PATH", global.env_copy[i], 4) == 0 && global.env_copy[i][4] == '=')
        {    
            global.path = ft_strdup(global.env_copy[i]);
            if (help(cmd))
                return 1;
        }
        i++;
    }
    return 0;
}

int     cmd_execution(char **cmd)
{
    pid_t pid;

    if (find_path(cmd))
    {
        pid =  fork();
        if (pid < 0)
            return 0;
        else if(pid == 0)
        {
            if (execve(global.path, cmd, global.env_copy) == -1)
                return 0;
        }
        else
            waitpid(pid, &global.status, 0);
        return 1;
    }
    // if (function)
        
    if (global.wall != 1)
        printf("Minishell : command not found : %s\n", cmd[0]);
    else 
        printf("Minishell: %s: No such file or directory\n", cmd[0]);
    //bash: KASDF: No such file or directory
    return 0;
}