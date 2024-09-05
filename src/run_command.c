/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:07:08 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 14:44:27 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*control_syntax(char *str, t_node *node)
{
	int	last;

	last = ft_strlen(str) - 1;
	while (last >= 0 && str[last] == ' ')
		last--;
	if (find_mark(str[last]))
	{
		exit_message(NULL, "Invalid syntax error", 1);
		return (NULL);
	}
	str = filter_input(str, node);
	return (str);
}

int	quotes_control(char *str)
{
	int	mark_flag;
	int	single_mark_flag;
	int	i;

	mark_flag = 0;
	single_mark_flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			single_mark_flag = !single_mark_flag;
		else if (str[i] == '"')
			mark_flag = !mark_flag;
		i++;
	}
	if (mark_flag || single_mark_flag)
	{
		exit_message(NULL, "Invalid syntax error", 1);
		return (0);
	}
	return (1);
}

int	compile_command(char *buf, t_node *node)
{
	buf = control_syntax(buf, node);
	if (!buf)
		return (0);
	if (!quotes_control(buf))
		return (0);
	node = lexer(buf, node);
	if (!node)
		return (0);
	if (!control_args(node) || !node_control(node, 1))
		return (0);
	set_last_command(node);
	return (1);
}

void	run_command(t_node *node, char ***envp, int *status, char *buf)
{
	if (compile_command(buf, node))
	{
		exec_node(node, 1);
		*envp = node->env;
		*status = node->last_status;
	}
	else
		*status = 1;
}
