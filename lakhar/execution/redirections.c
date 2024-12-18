/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:34 by rboulaga          #+#    #+#             */
/*   Updated: 2024/12/02 09:11:01 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int     redirections(s_input *input)
{
    printf(">dsf s dfsdfsdfsd\n");
    
    (void)global;
    if (input->tok == IN)
        printf("<\n");
    else if(input->tok == OUT)
        printf(">\n");
    return 0;
}