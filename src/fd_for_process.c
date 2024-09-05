/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_for_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaaydi <muhaaydi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:22:32 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 22:09:50 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>

void	fd_to_command(t_node *node, t_command *command)
{
	int	fd;

	if (!node || !command)
		return ;
	if (command->input_file)
	{
		fd = command->input_file;
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (node->prev_fd != 0)
	{
		dup2(node->prev_fd, STDIN_FILENO);
		close(node->prev_fd);
	}
	if ((!command->last_command && node->fd)
		|| (command->last_command && node->next))
	{
		dup2(node->fd[WRITE_NO], STDOUT_FILENO);
		close(node->fd[WRITE_NO]);
	}
}

void	writing_process(t_node *node, t_command *command)
{
	int	child_pid;
	int	status;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (!ft_strcmp(node->operator, ">"))
			write_file(node, command);
		else if (!ft_strcmp(node->operator, ">>"))
			add_text(node, command);
		if (node->prev_fd != 0)
			close(node->prev_fd);
		exit(EXIT_SUCCESS);
	}
	waitpid(child_pid, &status, 0);
	fork_exit(node, status);
}

int	redirect_file(t_node *node, int flag)
{
	t_command	*command;
	int			i;
	int			array[2];

	i = 0;
	node->fd = array;
	while (i < 2)
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
		else
			writing_process(node, command);
		i++;
	}
	return (1);
}
