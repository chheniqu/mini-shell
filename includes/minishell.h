/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:51:34 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 14:57:42 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include "../lib/libft/includes/libft.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_pipex_data	t_pipex_data;

typedef struct s_builtin	t_builtin;

typedef enum s_signal
{
	NO_SIG,
	SIG_INT,
	SIG_QUIT,
	SIG_TSTP,
}	t_signal;

typedef enum s_error
{
	SUCCESS,
	FAILURE,
}	t_error;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
	INVALID,
	INVALID2,
}	t_token_type;

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	t_quote			*quote;
}	t_token;

typedef struct s_redir
{
	char			*infile;
	char			*outfile;
	char			*here_doc_lim;
	int				is_here_doc;
	int				append;
	int				heredoc_read_fd;
	t_token_type	type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_shell_cmd
{
	char				*cmd_str;
	t_redir				*redir;
	struct s_shell_cmd	*next;
}	t_shell_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int				last_status;
	char			*read_line;
	t_env			*env;
	t_token			*token;
	t_shell_cmd		*shell_cmd;
	t_pipex_data	*pipex_data;
}	t_shell;

typedef struct s_expand
{
	int		i;
	int		j;
	int		k;
	char	*new_str;
}	t_expand;

typedef struct s_expand_var
{
	int		i;
	int		var_len;
	char	*value;
	char	*new_str;
	char	*var;
	t_env	*env;
}	t_expand_var;

typedef struct s_clean_data
{
	int		i;
	int		j;
	char	*word;
	char	current_quote;
	t_quote	*quotes;
}	t_clean_data;

typedef struct s_token_data
{
	char	*word;
	char	*clean_token;
	t_quote	*quote;
	t_quote	*clean_quotes;
}	t_token_data;

// minishell
void			init_minishell(t_shell *data);
void			ft_minishell(t_shell *data, char *line);
void			free_minishell(t_shell *shell_data);
void			protect_ft_minishell(void *ptr, t_shell *data, \
				char *sruct_name);
// parser
void			add_shell_cmd_to_list(t_shell_cmd **cmd_list, t_shell_cmd *new);
void			setup_redir_node(t_token *token, t_shell_cmd *cmd);
void			free_shell_cmd_list(t_shell_cmd *cmd_list);
void			free_redir_list_shell_cmd(t_shell_cmd *cmd);
void			add_redir_to_list(t_redir **redir_list, t_redir *new);
void			handle_pipe(t_shell_cmd **cmd_list, t_shell_cmd **cmd);
void			handle_cmd_node(t_token *token, t_shell_cmd **cmd);
void			handle_word(t_token *token, t_shell_cmd *cmd);
void			get_clean_shell_cmd(t_shell_cmd *cmd);
void			replace_all_heredocs(t_redir *redir, const char *lim);
char			*get_last_heredoc_lim(t_redir *redir);
t_redir			*create_redir_node(t_token *token);
t_shell_cmd		*create_shell_cmd(char *cmd_str);
t_shell_cmd		*parser(t_token *token);
int				check_spaces(t_token *token);

// syntax
t_token			*last_token(t_token *tokens);
int				is_redirection(t_token_type type);
bool			has_syntax_error(t_token *tokens);
t_token			*new_token(char *value, t_token_type type, t_quote *quote);
void			add_token_back(t_token **head, t_token *new);
void			free_tokens(t_token **tokens);
int				syntax_error(char *token);
// tokenization
char			*extract_word(char *line, int *i, t_quote **quote_str);
t_token_type	token_type(char *str, int *i);
char			*symbol_type(t_token_type type);
t_token			*tokenize(char *line);
int				check_quotes(char *s);
char			*remove_quotes(char *word, t_quote *quote, t_quote **new_quote);
t_token			*process_tokens(char *line, int *i);
// readline
void			read_prompt(t_shell *data);
// builtins
int				is_builtin(char *token_value);
void			exec_builtins(t_token *token, t_shell *shell);
int				ft_pwd(void);
int				ft_echo(t_token *token);
int				ft_cd(t_token *args, t_shell *shell);
void			update_env(t_shell *data, char *key, char *value);
int				ft_exit(t_token *args, t_shell *shell);
int				print_env(t_shell *shell);
t_env			*is_var(t_shell *shell, char *key);
void			export_var(t_shell *shell, char *arg);
int				ft_export(t_token *token, t_shell *shell);
int				check_key_format(char *str);
void			ft_unset(t_token *token, t_shell *shell);
void			remove_variable(t_shell *shell, char *key);
int				is_builtin(char *token_value);
// environnement
void			free_env(t_shell *data);
t_env			*create_env_node(char *key, char*value);
void			add_var_to_list(t_shell *data, t_env *new);
void			get_env(t_shell *data, char **env);
int				ft_env(t_token *builtin, t_shell *data);
// signals
void			handle_signals_parent(int sig);
void			handle_signals_child(int sig);
void			handle_signals_heredoc(int sig);
void			init_signals_heredoc(void);
void			init_signals_child(void);
void			init_signals_parent(void);
void			ignore_signals_parent(void);
// expand
void			expand_variable(t_token *token, t_shell *data);
char			*expand_value(char *str, char *to_remplace, char *var_name, \
				int dollar);
char			*is_in_env(t_env *env, char *var);
int				is_expand(t_token *token);

#endif
