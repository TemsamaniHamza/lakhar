/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:22:48 by rboulaga          #+#    #+#             */
/*   Updated: 2024/12/02 11:24:54 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int     join_var(char *var)
{
    int i;
   
    (void)global;
    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    if (var[i] == '=')
        return 1;
    return 0;
}


int     putstr(char *str)
{
    int i;
    int flag = 0;
    //flag usage if there is more than one = and we need just the first one

    i = 0;
    while (str[i])
    {
        printf("%c", str[i]);
        if (str[i] == '=' && flag == 0)
        {    
            printf("\"");
            flag = 1;
        }
        i++;
    }
    if (flag == 1)
        printf("\"");
    printf("\n");
    return 1;
}

void    sort_list(int len)
{
    int i;
    char *tmp;
    int j;

    i = 0;
    j = 0;
    while (i < len - 1)
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (global.env_copy[j][0] > global.env_copy[j + 1][0])
            {
                tmp = global.env_copy[j];
                global.env_copy[j] = global.env_copy[j + 1];
                global.env_copy[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}