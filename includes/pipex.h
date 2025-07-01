/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:12:45 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 12:49:16 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/includes/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include "minishell.h"

# define CMD_NOT_FOUND 127 
# define CMD_NOT_EXEC 126
# define ERROR_MSG 2

typedef enum s_p_error
{
	BAD_ARGS,
	BAD_FILE,
}	t_p_error;

typedef enum s_exec
{
	PARENT,
	CHILD,
}	t_exec;

typedef struct s_builtin
{
	char				*value;
	struct s_builtin	*next;
}	t_builtin;

typedef struct s_cmd
{
	char			*cmd_str;
	char			*clean_cmd;
	char			*cmd_path;
	char			**execve_av;
	int				pid;
	int				cmd_index;
	bool			is_directory;
	bool			is_builtin_parent;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex_data
{
	char		**env;
	char		**path;
	int			i;
	int			exit_status;
	int			**pipe_fd;
	int			pipes_count;
	int			cmd_count;
	t_cmd		*cmd_list;
}	t_pipex_data;

// check
char		*get_txt_error(char *txt, char *cmd);
int			check_infile(char *file_name, int fd);
int			check_outfile(char *file_name, int fd);
int			check_access(t_pipex_data *data, char *cmd);
void		check_punctuation(t_shell *shell_data, t_cmd *cmd);
int			is_directory(t_shell *shell_data, char *path);
void		check_directory(t_shell *shell_data, t_cmd *cmd);

// exec
void		ft_here_doc(char **av, int ac, t_pipex_data *data, char **env);
void		ft_pipe(t_shell *shell_data, char **env);
void		ft_pipex(t_shell *shell_data);

// parse
t_cmd		*create_cmd_node(char *cmd_str);
void		add_cmd_to_list(t_pipex_data *data, t_cmd *cmd);
void		get_shell_data(t_shell_cmd *shell_cmd, t_cmd *cmd);
void		get_clean_cmd(t_cmd *cmd, char *cmd_str);
void		get_path_tab(t_pipex_data *data, char **env);
void		get_cmd_path(t_shell *shell_data, t_cmd *cmd);
void		free_cmd_list(t_pipex_data *data);

// redirections
void		init_redir(t_shell *shell_data, t_cmd *cmd);
void		handle_infile_redirection(t_shell *shell, t_cmd *cmd, \
			t_redir *redir);
void		handle_outfile_redirection(t_shell *shell, t_cmd *cmd, \
			t_redir *redir);
int			has_redir_input(t_redir *redir);
int			has_redir_output(t_redir *redir);

// heredoc
void		handle_heredoc(t_shell *shell_data);
void		close_heredoc_read_fd(t_pipex_data *data);
void		close_heredoc_fd(t_cmd *cmd);
void		exec_builtins_in_child(t_shell *shell_data, t_cmd *cmd);
void		exec_builtins_in_parent(t_shell *shell_data, t_cmd *cmd);
t_token		*copy_until_redir(t_token *start);
t_token		*copy_until_pipe(t_token *start);
t_token		*find_start_token(t_token *token, int cmd_index);

// utils
void		init_pipes(t_pipex_data *data);
void		wait_for_children(t_shell *shell_data);
void		safe_dup2(int fd1, int fd2, t_pipex_data *data);
void		close_unused_pipes(t_pipex_data *data, int cmd_index);
void		close_all_pipes(t_pipex_data *data);
int			free_pipex(t_pipex_data *data, int exit_status);
void		free_token_builtin(t_token **tokens);
void		free_minishell_builtin(t_shell *shell_data);
void		init_ft_pipe(t_shell *shell_data, char **env);
void		handle_no_cmd_str(t_shell *shell_data);
char		**get_env_array(t_shell *data);

// split_minishell
char		**ft_split_minishell(char *str);
int			check_quote(char *s);
char		*ft_strncpy_minishell(char *s1, int n);
char		**free_tab_minishell(char **tab);
void		skip_quote_minishell(char *s, int *i, int *count);

#endif