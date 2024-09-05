/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:52:56 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 16:05:33 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_command(t_node *node)
{
	t_command	*command;
	int			i;

	i = 0;
	while (i < 2)
	{
		if (!i)
			command = node->left;
		else
			command = node->right;
		if (!command)
			break ;
		if (command->data)
			free(command->data);
		if (command->arg)
			free_array(command->arg);
		free(command);
		i++;
	}
}

void	node_free(t_node *node)
{
	t_node	*next;

	while (node)
	{
		next = node->next;
		free_command(node);
		if (node->operator)
			free(node->operator);
		free(node);
		node = next;
	}
}

void	exit_node(t_node *new_node)
{
	node_free(new_node);
	exit_message(NULL, "Allocation error\n", 0);
}

void	exit_allocation(t_node *node, char *str)
{
	if (str)
		free(str);
	exit_message(NULL, "Allocation error\n", 1);
	ft_exit(node, EXIT_FAILURE);
}
