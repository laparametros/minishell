/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_nodes3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:03:47 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 15:11:48 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*join_value(char *str, char *delim, t_command *command, t_node *node)
{
	char	*res;
	char	*trimmed;
	int		i;

	i = 0;
	res = pre_trim(str, delim, command, node);
	while (str[i] && str[i] != ' ')
		i++;
	if (!i)
		return (res);
	trimmed = ft_trim(str, str[i]);
	res = ft_strjoin(res, trimmed);
	if (!res)
	{
		exit_message(NULL, "Allocation error\n", 1);
		ft_exit(node, EXIT_FAILURE);
	}
	free(res);
	return (res);
}

char	*get_next_token(t_command *command, char *res, char *str, t_node *node)
{
	char	char_trim;
	char	*res2;

	char_trim = 0;
	res2 = NULL;
	if (command && command->quotes)
		res = filter_env(command, res, node);
	if (str && str[0] && str[0] != ' ')
	{
		char_trim = str[0];
		res2 = join_value(str, &char_trim, command, node);
	}
	if (res2)
	{
		res = ft_strjoin(res, res2);
		if (!res)
		{
			exit_message(NULL, "Allocation error\n", 1);
			ft_exit(node, EXIT_FAILURE);
		}
		if (res2)
			free(res2);
	}
	return (res);
}

char	*quotes_state(char *str, int i, t_node *node, t_command *command)
{
	char	char_trim;
	char	*res;

	char_trim = str[i];
	res = ft_strtok(&str[i], &char_trim, node);
	str = ft_memmove(str, &str[i + 1], ft_strlen(str));
	if (res[ft_strlen(res)] == ' ')
		res[ft_strlen(res)] = 0;
	if (command && char_trim != '\'')
		command->quotes = 1;
	else if (command)
		command->quotes = 0;
	res = get_next_token(command, res, str, node);
	if (command)
		command->quotes = 0;
	return (res);
}

char	*pre_trim(char *str, char *delim, t_command *command, t_node *node)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (!command || !(command->quotes))
		delim = " \"'";
	while (str[i] == ' ')
		i++;
	if (str[i] == '"' || str[i] == 39)
		return (quotes_state(str, i, node, command));
	res = ft_strtok(str, delim, node);
	if (command && res && res[0] != '\'')
		command->quotes = 1;
	return (get_next_token(command, res, str, node));
}
