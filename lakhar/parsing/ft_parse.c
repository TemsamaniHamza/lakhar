#include "../headers/minishell.h"

int check_beggining(char *str)
{
    s_token tok;

    tok = return_token(str[0], str[1]);
    if(tok == OR || tok == AND || tok == PIPE || tok == RPR)
    {
        printf("Error");
        global.exited = 258;
        return(0);
    }
    return(1);
}
s_input	*tokenizer(char *str)
{
	s_input	*input;
	int     parenthes;
	int     i;

	parenthes = 0;
	i = 0;
	input = NULL;

	while (str[i])
	{
		if (!token_1(&input, str, &i, &parenthes))
			return (free(str), NULL); 
	}
    free(str);
    str = NULL;
	return (input);
}

s_input *ft_parse(char *rl)
{
    char *str;
    s_input *input;

    str = ft_strtrim(rl, " \t\n\v\f\r");
    free(rl);
    if(!str || check_beggining(str) == 0)
    {
        free(str);
        return NULL;
    }
    input = tokenizer(str);
    if(!input)
        return NULL;
    input = shunting_yard(&input);
    while (input->right)
        input = input->right;
    input = list_to_tree(input);
    return(input);
}   