/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:04:06 by rboulaga          #+#    #+#             */
/*   Updated: 2024/10/23 14:28:59 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int		cd(char **cmd)
{
    char *tmp;
    int i = 0;
     
    while(cmd[i])
        i++; 
    if (i > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return 1;
    }
    else if (!cmd[1])
    {
        tmp = getenv("HOME");
        if (tmp)
            chdir(tmp);
    }
    else if (cmd[1])
    {
        if (chdir(cmd[1]) == 0)
            return 0;
        else
            printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
        return 1;
    }
    return 0;
}
