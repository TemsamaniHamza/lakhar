#include "../headers/minishell.h"

s_global global;  


int main(int argc, char **argv, char **env)
{
    char *rl;
    int fd_input;
    int fd_output;
	(void)argc;
	(void)argv;
    int i = 0;
    s_input *input;

    ft_initialize(env, &fd_input, &fd_output); 
    while(1)
    {
        rl = readline("minishell --> ");
        if(!rl)
            break;
        global.executed = 1;
        add_history(rl);
        input = ft_parse(rl);
        // printf("%d\n", input->tok);
        // exit(1);
        if(input == NULL)
            exit(1);
        ft_execute(input);
        global.executed = 0;
    }
	return 0;
}
