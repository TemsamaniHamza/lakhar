#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft_torename/libft.h"

typedef enum t_token
{
	IN,         // <		
	OUT,        // >		
	HEREDOC,    // <<		
	APPEND,     // >>		
	AND,        // &&		
	PIPE,       // |		
	OR,         // ||		
	LPR,        // (		
	RPR,        // )		
	STR,        // string	
	END         // end dyal cmd
}   s_token;

typedef struct t_redir
{
	s_token			tok;
	char			*file;
	int				flg;
	int				fd;
	struct t_redir	*left;
	struct t_redir	*right;
}s_redir;

typedef struct t_input
{
	s_token			tok;
	char			*command;
	char			**cmd;
	int				token_flag;
	struct t_input	*left;
	struct t_input	*right;
	s_redir			*redirections;
}   s_input;

typedef struct t_env
{
	char 			*env;
	char			*var;
	char			*value;
	struct s_env	*next;
}	s_env;

typedef struct t_global
{
	char 			**env;
	int 			executed;
	int 			exited;
}	s_global;

extern s_global global;






void    ft_initialize(char **env, int *fd_input, int *fd_output);
void ft_initialize_env(char **env);
void    save_input_output(int *fd_input, int *fd_output);
s_token	return_token(char c1, char c2);
s_input *ft_parse(char *rl);
int check_beggining(char *str);
int token_1(s_input **head, char *s, int *i, int *par);
s_input	*node_creation_cmd(char *s, s_redir *redir, s_token tok, int token_flag);
int	check_syntax_error(s_token tok, char *s);
int	check_syntax_help(s_token tok, s_token next);
int	check_spaces(char c);
int	check_rpr(char *s, int i);
int	check_not_operator(s_token tok);
int return_token_syntax(int tok,char *s, int *i,  int *par);
s_input	*token_2(char *s ,int *i ,s_token tok);
int	build_command_list(s_input **head, s_input *add);
s_input	*list_to_tree(s_input *root);
void	remove_top(s_input **tok_s);
void	push_2(s_input **top, s_input *to_add);
void	push(s_input **a_input, s_input **b_input, int flg);
s_input	*shunting_yard(s_input **input);
void	the_shunting_yard(s_input **input, s_input **tok_stack, s_input **new_stack);
int token_1(s_input **head, char *s, int *i, int *par);
int	build_command_list(s_input **head, s_input *add);
int	check_syntax_help(s_token tok, s_token next);
int	check_spaces(char c);
int	check_rpr(char *s, int i);
int	check_not_operator(s_token tok);
int	check_command(s_token tok);
void	incre(char *s, int *i);
int str_len(char *s, int i, int flg);
int	choose_str(char c, int flg);
char **prep_cmd(char *s, int *i, s_token tok, int flg);
char **fill_command(char *s, int l, int *k, int flg);
char	*cmd_help(char *s, int l, int *k, int flg);
void check_flg(int flg, char *s, int *k);
int check_next_quote(char *s, char c);
int	check_syntax(s_token tok, char *s);
int build_redir_list(s_redir **head, s_redir *add);
int	check_true(s_token tok);	
s_redir	*node_create_redirection(char **s, s_token tok);
void ft_execute(s_input *input);
void exec_str(s_input *input);
char **expand(char *command);
char **parsing_cmd(char *str);
int find_len(char *str);
int look_for_1_quote(char *str, int *i, char c);


#endif