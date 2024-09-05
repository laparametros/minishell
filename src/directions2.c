/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:01:49 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:51:00 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <signal.h>
#include <unistd.h>

extern int	g_pid;

int	append_to_file(t_node *node, int flag)
{
	t_command	*command;
	int			i;
	int			array[2];

	i = -1;
	node->fd = array;
	while (++i < 2)
	{
		pipe(node->fd);
		if (!i)
			command = node->left;
		else if (i)
			command = node->right;
		if (command == NULL)
			break ;
		if (!i && flag && command->type == OUTPUT)
			exit_message(NULL, "Command not found\n", 0);
		else if (command->type == COMMAND && flag && !i)
			send_command(node, command, i);
		else if (command->arg && command->arg[1] != NULL)
			exit_message(NULL, "Error - Invalid usage.\n", 0);
		else
			writing_process(node, command);
	}
	return (1);
}

void	input_from_user(int *pipefd, char *end_key)
{
	int		read_bytes;
	char	buf[1024];

	close(pipefd[0]);
	while (1)
	{
		write(1, ">> ", 3);
		read_bytes = read(STDIN_FILENO, buf, sizeof(buf));
		if (!read_bytes)
		{
			write(1, "\n", 1);
			exit(-1);
		}
		if (read_bytes == -1)
			break ;
		buf[read_bytes] = '\0';
		if (!ft_strcmp(buf, end_key))
			break ;
		write(pipefd[1], buf, ft_strlen(buf));
	}
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

int	get_heredoc(t_node *node, char *end_key)
{
	int		pipefd[2];
	int		status;
	int		child_pid;
	char	*end_key_copy;

	if (!ft_strlen(end_key))
		return (0);
	status = 0;
	end_key_copy = ft_strdup(end_key);
	end_key_copy = ft_strjoin(end_key_copy, "\n");
	pipe(pipefd);
	child_pid = fork();
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		input_from_user(pipefd, end_key_copy);
		exit(0);
	}
	g_pid = child_pid;
	waitpid(child_pid, &status, 0);
	g_pid = 0;
	return (free(end_key_copy), fork_exit(node, status),
		close(pipefd[1]), pipefd[0]);
}
