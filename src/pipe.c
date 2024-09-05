/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaaydi <muhaaydi@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:06:34 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/13 14:06:52 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>

int	pipe_execute(t_node *node)
{
	int			i;
	int			array[2];
	t_command	*command;

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
		send_command(node, command, i);
		i++;
	}
	return (0);
}
