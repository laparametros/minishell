/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:21:35 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:51:45 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_exit(t_node *node, long long int value)
{
	t_node	*temp;

	temp = node;
	while (temp && temp->prev)
		temp = temp->prev;
	if (temp->buf)
		free(temp->buf);
	free_array(node->env);
	node_free(node);
	rl_clear_history();
	exit(value);
}

int	exit_arg_control(t_node *node, unsigned long long int value, int isneg)
{
	if ((isneg == -1 && value > (unsigned long long) LONG_MIN)
		|| (isneg == 1 && value > (unsigned long long) LONG_MAX))
	{
		exit_message(NULL, "Error numeric argument required\n", 1);
		ft_exit(node, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

long long int	ft_latoi(const char *str, t_node *node)
{
	unsigned long long	nbr;
	int					isneg;
	int					i;

	i = 0;
	nbr = 0;
	isneg = 1;
	while (str[i] != '\0' && (str[i] == 32
			|| str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			isneg = -1;
		i++;
	}
	while (str[i] != '\0' && ((isneg == -1 && nbr < (unsigned long long)
				LONG_MIN) || (isneg == 1 && nbr
				< (unsigned long long) LONG_MAX)))
		nbr = (nbr * 10) + (str[i++] - '0');
	exit_arg_control(node, nbr, isneg);
	return ((long long int)(nbr * isneg));
}

int	ft_isnum(char *str)
{
	if (!*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	exit_command(t_node *node, char **args)
{
	long long int	value;

	printf("exit\n");
	if (args[1])
	{
		if (!ft_isnum(args[1]))
		{
			exit_message(NULL, "Error numeric argument required\n", 1);
			ft_exit(node, -1);
		}
		if (args[2])
			return (exit_message(NULL, "Too many arguments\n", 1));
		else
		{
			value = ft_latoi(args[1], node);
			ft_exit(node, value);
		}
	}
	ft_exit(node, 0);
	return (0);
}
