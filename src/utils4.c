/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaaydi <muhaaydi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:47:19 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 22:15:49 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	not_found_error(t_command *command, t_node *node)
{
	if (command && *command->data && ft_strcmp(node->operator, "<<"))
	{
		exit_message(command->data, "Command not found\n", 1);
		assign_status(node, 127);
	}
}
