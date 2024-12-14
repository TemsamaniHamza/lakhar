/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:42:59 by rabia             #+#    #+#             */
/*   Updated: 2024/12/02 09:52:20 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void ft_env()
{
    s_env *tmp;
    
    tmp = global.env;
    while(tmp)
    {
        if (find_char(tmp->env, '=') == -1)
        {
            tmp = tmp->next;
        }
        printf("%s\n",tmp->env);
        tmp = tmp->next;
    }
    global.exited = 0;
}
// ‘%s’ check if there is any problem