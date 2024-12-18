/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:41:39 by rabia             #+#    #+#             */
/*   Updated: 2024/11/28 22:10:33 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int	env_cmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
    if (str2[i] != '=')
    { 
        
        return (0);
    }
    return (1);
}

int     strcount(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    return (i);
}

int     unset(char **cmd)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (strcount(cmd) == 1)
        return 1;
    while (cmd[i])
    {
        while (global.env_copy[j])
        {        
            if(env_cmp(cmd[i], global.env_copy[j])) 
            {
                free(global.env_copy[j]);
                global.env_copy[j] = NULL;
                while (global.env_copy[j + 1])
                {
                    if (global.env_copy[j + 1])
                        global.env_copy[j] = global.env_copy[j + 1];
                    j++;
                }
                global.env_copy[j] = NULL;
                // free(global->env_copy);
            }
            j++;
        }
        j = 0;
        i++;
    }
    return 0;    
}