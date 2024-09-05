/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:46:17 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:55:50 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>

int	exit_message(char *str, char *message, int builtin_flag)
{
	if (!str)
		write(2, str, ft_strlen(str));
	write(2, message, ft_strlen(message));
	if (builtin_flag)
		return (EXIT_FAILURE);
	exit(-1);
}

void	fork_exit(t_node *node, int status)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		node->last_status = status;
		assign_status(node, status);
	}
	else if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		status += 128;
		node->last_status = status;
		assign_status(node, status);
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
		{
			return (NULL);
		}
		str++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	len;
	size_t	k;
	size_t	i;

	k = 0;
	i = ft_strlen((char *) s1);
	len = ft_strlen((char *) s1) + ft_strlen((char *) s2);
	temp = (char *) malloc(len + 1);
	if (!temp)
		return (NULL);
	while (i > k)
		*temp++ = s1[k++];
	k = 0;
	i = ft_strlen((char *) s2);
	while (i > k)
		*temp++ = s2[k++];
	if (ft_strlen((char *) s1))
	{
		free((char *) s1);
		s1 = NULL;
	}
	*(temp) = '\0';
	return (temp - len);
}

void	set_last_command(t_node *node)
{
	t_command	*left;
	t_command	*right;

	while (node->next)
		node = node->next;
	while (node)
	{
		left = node->left;
		right = node->right;
		if (right && right->type == COMMAND)
		{
			right->last_command = 1;
			break ;
		}
		else if (right && right->type == OUTPUT)
			return ;
		if (left && left->type == COMMAND)
		{
			left->last_command = 1;
			break ;
		}
		else if (left && left->type == OUTPUT)
			return ;
		node = node->prev;
	}
}
