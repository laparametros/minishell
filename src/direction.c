/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:55:50 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 21:04:21 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>
#include <fcntl.h>

int	g_pid = 0;

int	builtin_exec(t_command *command, t_node *node, int i)
{
	int	status;

	status = 0;
	if (!ft_strcmp(command->data, "echo"))
		status = (echo(command->arg));
	else if (!ft_strcmp(command->data, "cd"))
		status = (cd(command->arg));
	else if (!ft_strcmp(command->data, "pwd"))
		status = (pwd(node));
	else if (!ft_strcmp(command->data, "export"))
		status = (export(command->arg, node));
	else if (!ft_strcmp(command->data, "unset"))
		status = (unset(command->arg, node));
	else if (!ft_strcmp(command->data, "env"))
		status = (env(node->env));
	else if (!ft_strcmp(command->data, "exit"))
		status = (exit_command(node, command->arg));
	descriptor_for_builtins(node, command, i);
	return (status);
}

void	wait_fork(t_node *node, t_command *command, int child_pid, int i)
{
	int	status;

	g_pid = child_pid;
	waitpid(child_pid, &status, 0);
	g_pid = 0;
	fork_exit(node, status);
	if (command->input_file)
		close(command->input_file);
	if (node->prev_fd != 0)
		close(node->prev_fd);
	if (!i && node->fd && ft_strcmp("<<", node->operator))
		node->prev_fd = node->fd[READ_NO];
	else if (node->next && ((node->fd && i)
			|| (!i && node->right->type == OUTPUT)))
		node->next->prev_fd = node->fd[READ_NO];
}

void	*send_command(t_node *node, t_command *command, int i)
{
	pid_t	child_pid;
	int		saved;

	saved = dup(STDOUT_FILENO);
	fd_to_command(node, command);
	if (!command || command->type == OUTPUT)
		not_found_error(command, node);
	else if (is_builtin(command->data))
		assign_status(node, builtin_exec(command, node, i));
	else
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			execute_command(command, node->last_status, node->env, node);
			exit(0);
		}
		else
			return (wait_fork(node, command, child_pid, i),
				dup2(saved, STDOUT_FILENO), NULL);
	}
	return (dup2(saved, STDOUT_FILENO), NULL);
}

void	write_file(t_node *node, t_command *command)
{
	int		fd;
	int		res;
	char	readbuffer[100];

	if (command->arg)
	{
		if (command->arg[1] != NULL)
		{
			exit_message(NULL, "Error - Invalid usage.\n", 1);
			return ;
		}
	}
	fd = open(command->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
	res = read(node->prev_fd, readbuffer, 100);
	while (res > 0)
	{
		write(fd, readbuffer, res);
		res = read(node->prev_fd, readbuffer, 100);
	}
	close(fd);
	if (node->prev_fd != 0)
		close(node->prev_fd);
	exit(EXIT_SUCCESS);
}

void	*add_text(t_node *node, t_command *command)
{
	char	readbuffer[100];
	int		fd;
	int		res;

	if (command->arg)
	{
		if (command->arg[1] != NULL)
			return (exit_message(NULL, "Error - Invalid usage.\n", 1), NULL);
	}
	fd = open(command->data, O_RDWR | O_APPEND | O_CREAT, 0644);
	res = read(node->prev_fd, readbuffer, 100);
	while (res > 0)
	{
		write(fd, readbuffer, res);
		res = read(node->prev_fd, readbuffer, 100);
	}
	close(fd);
	fd = open(command->data, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (node->next && ft_strcmp(node->next->operator, ">") == 0)
		node->next->prev_fd = fd;
	if (node->prev_fd != 0)
		close(node->prev_fd);
	exit(EXIT_SUCCESS);
}
