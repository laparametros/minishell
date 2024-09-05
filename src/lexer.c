/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:02:21 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 17:13:22 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*delete_quote(t_command *current_command, char *token)
{
	char	*temp;

	if (token[0] != 39)
		current_command->quotes = 1;
	if (token[0] == 39 || token[0] == '"')
	{
		temp = token;
		token = ft_strdup(&token[1]);
		free(temp);
	}
	return (token);
}

t_command	*add_token(t_node *node, t_command *current_command,
						char *token, int *arg_flag)
{
	if (*arg_flag)
		current_command->arg = remake_arguments(current_command->arg,
				token, node);
	else
	{
		*arg_flag = 1;
		current_command = init_leaf(node, token);
		current_command->arg = remake_arguments(NULL, token, node);
	}
	return (current_command);
}

t_command	*first_cleaning(char *token, t_node *node, int *arg_flag)
{
	t_command	*command;

	command = NULL;
	if (!ft_strcmp(token, "|") || !ft_strcmp(token, "<<")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">") | !ft_strcmp(token, "|"))
	{
		exit_message(NULL, "Error - Invalid Syntax.", 1);
		return (NULL);
	}
	command = init_leaf(node, token);
	command->arg = remake_arguments(NULL, token, node);
	*arg_flag = 1;
	return (command);
}

t_node	*add_node(t_node *node, int *arg_flag, char *token)
{
	if (!node->operator)
	{
		node->operator = ft_strdup(token);
		free(token);
	}
	else
		node = create_node(node, token);
	*arg_flag = 0;
	return (node);
}

t_node	*lexer(char *str, t_node *node)
{
	char		*token;
	t_command	*command;
	t_node		*root;
	int			arg_flag;
	int			res;

	token = pre_trim(str, " ", NULL, node);
	root = node;
	command = first_cleaning(token, node, &arg_flag);
	if (!command)
		return (free(token), NULL);
	while (1)
	{
		token = pre_trim(str, " ", command, node);
		if (!token)
			break ;
		res = find_operator(token);
		if (token && res != 0)
			node = add_node(node, &arg_flag, token);
		else if (token)
			command = add_token(node, command, token, &arg_flag);
	}
	return (root);
}
