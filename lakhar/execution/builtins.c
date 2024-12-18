/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:24:54 by rabie             #+#    #+#             */
/*   Updated: 2024/12/01 11:39:27 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int    builtins(char **cmd)
{    
    if (ft_ncmp("echo", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
        return(echo(cmd), 1);
    else if (ft_ncmp("pwd", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
        return(pwd(), 1);
    else if (ft_ncmp("cd", cmd[0], 2) == 0 && ft_strlen(cmd[0]) == 2)
        return(cd(cmd), 1);
    else if (ft_ncmp("env", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
        return(env(cmd), 1);
    else if (ft_ncmp("unset", cmd[0], 5) == 0 && ft_strlen(cmd[0]) == 5)
        return(unset(cmd), 1);
    else if (ft_ncmp("export", cmd[0], 6) == 0 && ft_strlen(cmd[0]) == 6)
        return(export(cmd), 1);
    else
        cmd_execution(cmd);
    free_list(cmd);
    return 0;
}

