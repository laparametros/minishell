/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_nodes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:28:05 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 15:04:51 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	assign_env(char **arg, int last_status)
{
	int		i;

	if (!arg)
		return ;
	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '$' && arg[i][1] == '?')
		{
			arg[i] = ft_itoa(last_status);
			break ;
		}
		i++;
	}
}

void	assign_status(t_node *node, int status)
{
	if (!node)
		return ;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		node->last_status = status;
		node = node->next;
	}
}

void	update_env(t_node *node, char **env)
{
	if (!node)
		return ;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		node->env = env;
		node = node->next;
	}
}
