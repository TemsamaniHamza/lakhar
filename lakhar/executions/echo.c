/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:25:47 by rabie             #+#    #+#             */
/*   Updated: 2024/10/21 13:01:57 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int check_option(char *str)
{
    int i;

    i = 0;
    if (str[0] == '-')
        i++;
    else
        return 0;
    while (str[i] == 'n')
        i++;
    if (str[i] == '\0')
        return 1;
    else
        return 0;        
}
//0 mean with newline
//1 mean without newline
void    echo(char **cmd)
{
    int newline;
    int j;

    j = 1;
    newline = 0;
    if(cmd[1])    
        newline = check_option(cmd[1]);
    while (cmd[j])
    {
        if (check_option(cmd[j]))
            j++;
        else
            break;
    }
    while (cmd[j])
    {   
        printf("%s", cmd[j]);
        printf(" ");
        j++;
    }    
    if(newline == 0)
        printf("\n");
}

