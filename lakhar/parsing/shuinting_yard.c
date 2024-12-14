#include "../headers/minishell.h"

void	the_shunting_yard(s_input **input, s_input **tok_stack, s_input **new_stack)
{
	while (*input)
	{
		if ((*input)->tok == STR)
			push(input, new_stack, 0);
		else if ((*input)->tok != LPR && (*input)->tok != RPR)
		{
			while (*tok_stack && (*tok_stack)->token_flag >= (*input)->token_flag)
				push(tok_stack, new_stack, 0);
			push(input, tok_stack, 1);
		}
		else if ((*input)->tok == LPR)
			push(input, tok_stack, 1);
		else if ((*input)->tok == RPR)
		{
			remove_top(input);
			while ((*tok_stack)->tok != LPR)
				push(tok_stack, new_stack, 0);
			remove_top(tok_stack);
		}
	}
}

s_input	*shunting_yard(s_input **input)
{
	s_input	*tok_stack;
	s_input	*new_stack;

	tok_stack = NULL;
	new_stack = NULL;
	the_shunting_yard(input, &tok_stack, &new_stack);
	while (tok_stack)
		push(&tok_stack, &new_stack, 0);
	return (new_stack);
}

void	push(s_input **a_input, s_input **b_input, int flag)
{
	s_input	*sep;

	if (!a_input || !(*a_input))
		return ;
	sep = *a_input;
	*a_input = (*a_input)->right;
	sep->right = NULL;
	if (*a_input)
		(*a_input)->left = NULL;
	if (flag == 1)
		push_2(b_input, sep);
	else
		build_command_list(b_input, sep);
}

void	push_2(s_input **top, s_input *to_add)
{
	if (!to_add)
		return ;
	else if (!*top)
		*top = to_add;
	else
	{
		(*top)->left = to_add;
		to_add->right = *top;
		*top = to_add;
	}
}

void	remove_top(s_input **tok_s)
{
	if (!(*tok_s)->right)
	{
		free(*tok_s);
		*tok_s = NULL;
	}
	else
	{
		*tok_s = (*tok_s)->right;
		free((*tok_s)->left);
		(*tok_s)->left = NULL;
	}
}