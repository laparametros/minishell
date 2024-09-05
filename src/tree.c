/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:25:48 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 19:20:13 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**remake_arguments(char **argument_array, char *arg, t_node *node)
{
	int		i;
	int		len;
	char	**new_array;

	len = -1;
	i = 0;
	if (!arg)
		return (argument_array);
	if (!*arg)
		return (free(arg), argument_array);
	while (argument_array && argument_array[i])
		i++;
	new_array = (char **) malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		exit_allocation(node, arg);
	null_to_array(new_array, i + 2);
	while (++len < i && argument_array)
		new_array[len] = argument_array[len];
	new_array[len] = arg;
	new_array[len + 1] = NULL;
	if (argument_array)
		free(argument_array);
	return (new_array);
}

void	free_node_properties(t_command *delete_command, t_node *delete_node)
{
	free(delete_command->data);
	free_array(delete_command->arg);
	free(delete_node->operator);
	free(delete_node);
}

t_node	*delete_node(t_node *old, t_node *new)
{
	t_command	*temp;

	temp = NULL;
	if (old->right)
	{
		temp = old->right;
		old->right = new->left;
		old->operator = ft_strdup(new->operator);
		if (new->next)
		{
			new->next->prev = old;
			old->next = new->next;
		}
		else
			old->next = NULL;
		return (free_node_properties(temp, new), old);
	}
	else if (old->left)
	{
		old->prev->next = new;
		new->prev = old->prev;
	}
	return (free_node_properties(old->left, old), new);
}

void	assign_to_command(t_node *node, int file)
{
	while (node)
	{
		if (node->right && node->right->type == COMMAND)
		{
			node->right->input_file = file;
			break ;
		}
		else if (node->left && node->left->type == COMMAND)
		{
			node->left->input_file = file;
			break ;
		}
		node = node->prev;
	}
}

t_node	*send_operator(t_node *node, t_command *command, int flag, int i)
{
	if (!i && node->right && node->left)
		return (node);
	else if (!ft_strcmp(node->operator, ">"))
		node = direction_mark(node, command, flag, i);
	else if (!ft_strcmp(node->operator, ">>"))
		node = append_direction(node, command, flag, i);
	else if (!ft_strcmp(node->operator, "<"))
		node = input_mark(node, command);
	else if (!ft_strcmp(node->operator, "<<"))
		node = heredoc_mark(node, command);
	if (!i && command != node->left)
		send_operator(node, node->left, flag, i);
	else if (i && node->right && command != node->right)
		send_operator(node, node->right, flag, i);
	return (node);
}
