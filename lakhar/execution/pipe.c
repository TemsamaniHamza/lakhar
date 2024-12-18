/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:47:51 by rboulaga          #+#    #+#             */
/*   Updated: 2024/12/02 09:10:45 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


// void    left_child(s_input *input, s_global *global, int *pipefd)
// {
    
// }

int     single_pipe(s_input *input)
{
    char **tmp1;
    char **tmp2;
    int pipefd[2];

    pipe(pipefd);
    pid_t left = fork();
    if (left == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        if (input->left->tok == PIPE)
            single_pipe(input->left);    
        if (input->left->command)
        {
            tmp1 = ft_split(input->left->command, ' ');    
            builtins(tmp1);
        }
        exit(0);
    }
    pid_t right = fork();
    if (right == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        tmp2 = ft_split(input->right->command, ' ');
        builtins(tmp2);
        exit(0);
    }
    close(pipefd[1]);
    close(pipefd[0]);    
    
    waitpid(left, NULL, 0);
    waitpid(right, NULL, 0);   
    return 0;
}   
int     exe(char **cmd ,s_input *input)
{
    
    if (input->tok == PIPE)
        single_pipe(input);
    else if (input->tok == STR)
        builtins(cmd);
    // else if (input->tok == IN || input->tok == OUT)
    // {    
    //     redirections(input, global);    
    //     printf(">dsfsdfsdfsdfsd\n");
    // }
    return 0;
}
    
    
    
    
    
    
    
    
    
    
    //-->>>> explanation of tree <<<<-
    // if (input->tok == PIPE)
    //     printf("this is pipe\n");
    // printf("this is right->second command = %s\n", input->right->command);
    // input = input->left;
    // if (input->tok == PIPE)
    //     printf("this is pipe\n");
    // printf("this is left->first command = %s\n", input->left->command);
    // printf("this is right->second command = %s\n", input->right->command);
    