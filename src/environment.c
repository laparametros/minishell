/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:41:11 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 21:16:15 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_env(char *env, t_node *node)
{
	char	*path;
	char	*copy_path;

	if (!ft_strcmp(env, "?"))
	{
		free(env);
		return (ft_itoa(node->last_status));
	}
	path = ft_getenv(node->env, env, node);
	if (!path)
	{
		free(env);
		return (NULL);
	}
	copy_path = ft_strdup(path);
	free(env);
	return (copy_path);
}

char	*special_chars(char *env, t_node *node, char *str, char *token)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = -1;
	while ((env[i] == '?' && i == 0)
		|| (env[i] && !is_special(env[i])))
		i++;
	temp = (char *) malloc(sizeof(char) * (i + 1));
	if (!temp)
	{
		free(env);
		if (token)
			free(token);
		if (str)
			free(str);
		exit_allocation(node, NULL);
	}
	while (++j < i)
		temp[j] = env[j];
	temp[j] = 0;
	return (temp = get_env(temp, node), temp = ft_strjoin(temp, &env[i]), temp);
}

char	*cut_quotes(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (NULL);
	while (token[i] && token[i] != '"')
		i++;
	return (ft_trim(token, token[i]));
}

char	*cut_dollar(char *token, int *flag, t_node *node)
{
	char	*res;

	res = NULL;
	if (!token)
		return (NULL);
	*flag = 0;
	if (token[0] == '$')
		*flag = 1;
	res = ft_strtok(token, "$", node);
	if (!res && token[0] == '$' && !token[1])
	{
		if (!token[1])
			token[0] = 0;
		res = ft_strdup("$");
		*flag = 0;
	}
	return (res);
}

char	*filter_env(t_command *current_command, char *token, t_node *node)
{
	char	*res;
	char	*temp;
	char	*str;
	int		flag;

	temp = NULL;
	str = NULL;
	token = cut_quotes(token);
	res = cut_dollar(token, &flag, node);
	while (token && current_command->quotes && res)
	{
		if (flag && (!res || !*res || (is_special(res[0]) && res[0] != '?')))
			temp = res;
		else if (res && flag)
			temp = special_chars(res, node, str, token);
		str = get_str_for_env(str, temp, res, flag);
		free(res);
		if (temp)
			free(temp);
		temp = NULL;
		res = cut_dollar(token, &flag, node);
	}
	return (current_command->quotes = 0, free(token), str);
}
