/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:23:12 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:53:18 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_pid;

int	find_mark(char c)
{
	if (!c)
		return (0);
	if (c == '>')
		return (1);
	else if (c == '<')
		return (2);
	else if (c == '|')
		return (3);
	return (0);
}

char	*filter_input(char *str, t_node *node)
{
	int	i;
	int	res;
	int	res2;

	i = 0;
	while (str[i])
	{
		res = find_mark(str[i]);
		res2 = find_mark(str[i + 1]);
		if (res == res2 && res)
		{
			str = add_spaces(str, i, node);
			if (str[i] == ' ')
				i++;
			while (str[i] != ' ')
				i++;
		}
		else if (res > 0 && res2 > 0)
			return (exit_message(NULL, "Invalid syntax error", 1), NULL);
		else if (res && !res2)
			str = add_space(str, i, node);
		i++;
	}
	return (str);
}

void	final_state(t_node *node)
{
	node_free(node);
	free_array(node->env);
	rl_clear_history();
	exit(-1);
}

t_node	*new_prompt(t_node *node, int status, char **envp)
{
	t_node	*new_node;

	node_free(node);
	new_node = NULL;
	new_node = init_root(envp);
	new_node->last_status = status;
	return (new_node);
}

void	get_input(t_node *node)
{
	char	*buf;
	int		status;
	int		saved_stdin;

	status = 0;
	saved_stdin = dup(STDIN_FILENO);
	buf = NULL;
	while (1)
	{
		buf = readline("minishell@42$ ");
		if (ft_strlen(buf) > 0)
		{
			add_history(buf);
			node->buf = buf;
			run_command(node, &(node->env), &status, buf);
			node = new_prompt(node, status, node->env);
			dup2(saved_stdin, STDIN_FILENO);
		}
		else if (!buf)
			final_state(node);
		if (buf)
			free(buf);
		buf = NULL;
		g_pid = 0;
	}
}
