/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:28 by rabie             #+#    #+#             */
/*   Updated: 2024/10/20 12:36:08 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int    pwd()
{
    char buff[PATH_MAX];

    getcwd(buff, sizeof(buff));
    printf("%s\n", buff);
    return 0;
}



// one possible error is if the current directory has been deleted or unmounted.

