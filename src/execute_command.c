/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:20:55 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 21:02:29 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>

int	execute_command(t_command *command, int last_status,
		char **envp, t_node *node)
{
	if (command)
	{
		assign_env(command->arg, last_status);
		execve(get_location(command->arg[0], envp, node), command->arg, envp);
		exit(EXIT_FAILURE);
	}
	return (1);
}
