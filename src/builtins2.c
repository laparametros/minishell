/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:55:19 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 16:27:54 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <stdio.h>
#include <unistd.h>

char	*get_working_dir(t_node *node)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		exit_message(NULL, "Allocation error \n", 1);
		ft_exit(node, EXIT_FAILURE);
	}
	return (dir);
}

int	pwd(t_node *node)
{
	char	*dir;

	dir = get_working_dir(node);
	if (dir)
	{
		printf("%s\n", dir);
		free(dir);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	descriptor_for_builtins(t_node *node, t_command *command, int i)
{
	if ((node->right && ft_strcmp(command->data,
				node->right->data)) || node->next)
	{
		if (command->input_file)
			close(command->input_file);
		if (command->last_command)
			return ;
		if (node->prev_fd != 0)
			close(node->prev_fd);
		if (node->fd && ((node->next && i == 1)
				|| (!node->right && node->next)))
			node->next->prev_fd = node->fd[READ_NO];
		else if (!i && node->fd)
			node->prev_fd = node->fd[READ_NO];
	}
}
