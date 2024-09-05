/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:55:42 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 19:32:10 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	node_control(t_node *node, int flag)
{
	t_command	*command;
	int			i;

	if (!node)
		return (1);
	i = 0;
	while (i < 2)
	{
		if (!i)
			command = node->left;
		if (i)
			command = node->right;
		if (!command)
			break ;
		node = send_operator(node, command, flag, i);
		i++;
	}
	node_control(node->next, 0);
	return (1);
}

int	control_args(t_node *node)
{
	t_command	*command;
	int			i;
	char		*res;

	if (!node)
		return (0);
	i = 0;
	while (i < 2)
	{
		if (!i)
			command = node->left;
		if (i)
			command = node->right;
		if (!command)
			break ;
		res = get_location(command->data, node->env, node);
		if (res)
		{
			if (ft_strcmp(command->data, res))
				free(res);
			command->type = 1;
		}
		i++;
	}
	return (control_args(node->next), 1);
}
