/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:51:54 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:42:48 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define READ_NO 0
# define WRITE_NO 1
# define LAST 1

# include <stdlib.h>

extern int	g_pid;

enum e_command_type
{
	OUTPUT,
	COMMAND,
};

typedef struct s_command
{
	char	*data;
	char	**arg;
	int		input_file;
	int		last_command;
	int		type;
	int		quotes;
}	t_command;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	char			*operator;
	int				*fd;
	int				last_node;
	int				prev_fd;
	int				last_status;
	int				exitted;
	t_command		*left;
	t_command		*right;
	char			*buf;
	char			**env;
}	t_node;

//int
int			pipe_execute(t_node *node);
int			redirect_file(t_node *node, int flag);
int			ft_strcmp(char *s1, char *s2);
int			file_exist(char *file);
int			file_exist_writing(char *file);
int			append_to_file(t_node *node, int flag);
int			file_exist_append(char *file);
int			get_heredoc(t_node *node, char *end_key);
int			find_operator(char *str);
int			execute_command(t_command *command, int last_status,
				char **envp, t_node *node);
int			find_mark(char c);
int			is_builtin(char *str);
int			env(char **envp);
int			exit_command(t_node *node, char **args);
int			pwd(t_node *node);
int			cd(char **args);
int			echo(char **args);
int			unset(char **args, t_node *node);
int			export(char **args, t_node *node);
int			ft_atoi(const char *str);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_isalnum(int c);
int			node_control(t_node *node, int flag);
int			control_args(t_node *node);
int			ft_isdigit(int c);
int			exit_message(char *str, char *message, int builtin_flag);
int			is_special(char c);
//size_t
size_t		ft_strlen(char *str);
//char*
char		*get_location(char *command, char **envp, t_node *node);
char		*replace_str(char *str, int index, t_node *node);
char		*ft_strtok(char *str, char *delim, t_node *node);
char		*ft_strdup(char *src);
char		*add_space(char *str, int i, t_node *node);
char		*add_spaces(char *str, int i, t_node *node);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*filter_env(t_command *current_arg, char *token, t_node *node);
char		*get_working_dir(t_node *node);
char		*filter_input(char *str, t_node *node);
char		*ft_getenv(char **envp, char *key, t_node *node);
char		*ft_trim(char *str, char c);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
char		*ft_itoa(int n);
char		*ft_strcpy(char *s1, char *s2);
char		*pre_trim(char *str, char *delim, t_command *command, t_node *node);
char		**remake_arguments(char **argument_array,
				char *arg, t_node *exec_node);
char		**copy_array(char **array, int size);
char		*get_str_for_env(char *str, char *temp, char *res, int flag);
//void
void		null_to_array(char **array, int length);
void		assign_to_command(t_node *node, int file);
void		*add_text(t_node *node, t_command *command);
void		fork_exit(t_node *node, int status);
void		assign_env(char **arg, int last_status);
void		assign_status(t_node *node, int status);
void		writing_process(t_node *node, t_command *command);
void		exec_node(t_node *root, int flag);
void		kill_input(int signal);
void		update_env(t_node *node, char **env);
void		node_free(t_node *node);
void		free_array(char **str);
void		set_last_command(t_node *node);
void		run_command(t_node *node, char ***envp, int *status, char *buf);
void		fd_to_command(t_node *node, t_command *command);
void		write_file(t_node *node, t_command *command);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*send_command(t_node *node, t_command *command, int i);
void		ft_exit(t_node *node, long long int value);
void		exit_node(t_node *new_node);
void		exit_allocation(t_node *node, char *str);
void		descriptor_for_builtins(t_node *node, t_command *command, int i);
void		get_input(t_node *node);
void		not_found_error(t_command *command, t_node *node);
//t_node
t_node		*delete_node(t_node *old, t_node *new);
t_node		*init_root(char **env);
t_node		*create_node(t_node *node, char *token);
t_node		*lexer(char *str, t_node *node);
t_node		*lexer(char *str, t_node *node);
t_node		*direction_mark(t_node *node, t_command *command, int flag, int i);
t_node		*append_direction(t_node *node, t_command *command,
				int flag, int i);
t_node		*input_mark(t_node *node, t_command *command);
t_node		*heredoc_mark(t_node *node, t_command *command);
t_node		*send_operator(t_node *node, t_command *command, int flag, int i);
//t_command
t_command	*init_arg(t_node *node);
t_command	*init_leaf(t_node *node, char *token);
#endif // !SHELL_H
