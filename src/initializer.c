/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:01:14 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 16:19:50 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_node	*init_root(char **env)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
	{
		free_array(env);
		exit_message(NULL, "Allocation error\n", 0);
	}
	node->left = NULL;
	node->right = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->fd = 0;
	node->prev_fd = 0;
	node->exitted = 0;
	node->last_status = 0;
	node->env = env;
	node->operator = NULL;
	node->buf = NULL;
	return (node);
}

t_command	*init_arg(t_node *node)
{
	t_command	*arg;

	arg = (t_command *) malloc(sizeof(t_command));
	if (!arg)
	{
		ft_exit(node, EXIT_FAILURE);
		exit_message(NULL, "Allocation error\n", 0);
	}
	arg->data = NULL;
	arg->input_file = 0;
	arg->arg = NULL;
	arg->last_command = 0;
	arg->quotes = 0;
	return (arg);
}

t_command	*init_leaf(t_node *node, char *token)
{
	t_command	*current_arg;

	current_arg = NULL;
	if (!node->left)
	{
		node->left = init_arg(node);
		node->left->data = ft_strdup(token);
		if (!node->left->data)
			exit_allocation(node, NULL);
		current_arg = node->left;
		current_arg->type = 0;
	}
	else if (!node->right)
	{
		node->right = init_arg(node);
		node->right->data = ft_strdup(token);
		if (!node->left->data)
			exit_allocation(node, NULL);
		current_arg = node->right;
		current_arg->type = 0;
	}
	return (current_arg);
}

int	find_operator(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (2);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	else if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

t_node	*create_node(t_node *node, char *token)
{
	t_node		*new_node;
	t_command	*argument;

	new_node = init_root(node->env);
	node->next = new_node;
	new_node->prev = node;
	if (find_operator(token))
	{
		new_node->operator = ft_strdup(token);
		if (!new_node->operator)
			exit_node(new_node);
		free(token);
	}
	else
	{
		argument = init_leaf(node, token);
		if (!new_node->operator)
			exit_node(new_node);
		argument->arg = remake_arguments(NULL, token, node);
	}
	return (new_node);
}
