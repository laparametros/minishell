/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:51:16 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:54:44 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>

void	exec_node(t_node *root, int flag)
{
	t_node	*node;
	int		array[2];

	node = root;
	if (!node)
		return ;
	if (!node->next)
		node->last_node = 1;
	if (node->operator && !ft_strcmp(node->operator, ">"))
		redirect_file(node, flag);
	else if (node->operator && !ft_strcmp(node->operator, ">>"))
		append_to_file(node, flag);
	else if (node->operator && !ft_strcmp(node->operator, "|"))
		pipe_execute(node);
	else
	{
		if (node->next)
		{
			pipe(array);
			node->fd = array;
		}
		send_command(node, node->left, 0);
	}
	exec_node(node->next, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_node		*node;	

	argc++;
	if (argv)
		argv++;
	envp = copy_array(envp, 0);
	if (!envp)
		exit_message(NULL, "Allocation error\n", 0);
	signal(SIGINT, kill_input);
	signal(SIGQUIT, SIG_IGN);
	node = init_root(envp);
	get_input(node);
}
