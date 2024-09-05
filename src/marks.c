/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:04:17 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:54:37 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>

t_node	*direction_mark(t_node *node, t_command *command, int flag, int i)
{
	int	fd;

	if ((i && command->type == COMMAND)
		|| (!flag && !i && command->type == COMMAND))
		command->type = OUTPUT;
	if (command->type == OUTPUT && command->arg[1])
		exit_message(NULL, "Error invalid syntax\n", 0);
	if (command->type == OUTPUT)
	{
		fd = file_exist_writing(command->data);
		close(fd);
	}
	if (node->next && command->type == OUTPUT
		&& (!ft_strcmp(node->next->operator, ">")
			|| !ft_strcmp(node->next->operator, ">>")))
		node = delete_node(node, node->next);
	return (node);
}

t_node	*append_direction(t_node *node, t_command *command, int flag, int i)
{
	int	fd;

	if (!flag && !i && command->type == COMMAND)
		exit_message(NULL, "Error invalid syntax\n", 0);
	if ((i && command->type == COMMAND)
		|| (!flag && !i && command->type == COMMAND))
		command->type = OUTPUT;
	if (command->type == OUTPUT && command->arg[1])
		exit_message(NULL, "Error invalid syntax\n", 0);
	if (command->type == OUTPUT)
	{
		fd = file_exist_append(command->data);
		close(fd);
	}
	if (node->next && command->type == OUTPUT
		&& (!ft_strcmp(node->next->operator, ">")
			|| !ft_strcmp(node->next->operator, ">>")))
		node = delete_node(node, node->next);
	return (node);
}

t_node	*input_mark(t_node *node, t_command *command)
{
	int	fd;

	fd = file_exist(command->data);
	command->type = OUTPUT;
	if (node->next && (!ft_strcmp(node->next->operator, "<")
			|| !ft_strcmp(node->next->operator, "<<"))
		&& command->type == OUTPUT)
		node = delete_node(node, node->next);
	else
		assign_to_command(node, fd);
	return (node);
}

t_node	*heredoc_mark(t_node *node, t_command *command)
{
	int	fd;

	command->type = OUTPUT;
	fd = get_heredoc(node, command->data);
	if (node->next && (!ft_strcmp(node->next->operator, "<")
			|| !ft_strcmp(node->next->operator, "<<"))
		&& command->type == OUTPUT)
		node = delete_node(node, node->next);
	else if (!node->last_status)
		assign_to_command(node, fd);
	return (node);
}
