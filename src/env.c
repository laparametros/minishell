/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:43:43 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 22:29:26 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_getenv(char **envp, char *key, t_node *node)
{
	int				i;
	char			*temp;
	char			*res;

	i = 0;
	while (envp[i])
	{
		temp = ft_strnstr(envp[i], key, ft_strlen(key));
		if (temp)
		{
			res = ft_strdup(&temp[ft_strlen(key) + 1]);
			if (!res)
			{
				exit_message(NULL, "Allocation error\n", 0);
				ft_exit(node, EXIT_FAILURE);
			}
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	**update_environment_variable(char **envp, char *key, char *value)
{
	int		i;
	char	*new_variable;
	char	**new_envp;

	new_variable = ft_strdup(key);
	if (!new_variable)
		return (NULL);
	new_variable = ft_strjoin(new_variable, "=");
	if (!new_variable)
		return (NULL);
	new_variable = ft_strjoin(new_variable, value);
	free(value);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
			return (envp[i] = new_variable, envp);
		i++;
	}
	new_envp = copy_array(envp, i + 1);
	if (!new_envp)
		return (NULL);
	return (new_envp[i] = new_variable,
		new_envp[i + 1] = NULL, free_array(envp), new_envp);
}

int	control_expression(char *expression)
{
	if ((expression[0] >= 'A' && expression[0] <= 'Z')
		|| (expression[0] >= 'a' && expression[0] <= 'z')
		|| (expression[0] == '_'))
		return (1);
	else
		return (0);
}

char	*ft_trim(char *str, char c)
{
	char	*res;
	int		i;
	int		len;

	if (!str)
		NULL;
	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != c)
		i++;
	res = (char *) malloc(i + 1);
	if (!res)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (++i < len && str[i] != c)
		res[i] = str[i];
	if (*str)
		free(str);
	res[i] = 0;
	return (res);
}

int	export(char **args, t_node *node)
{
	int		i;
	char	*key;
	char	**envp;

	i = 0;
	envp = node->env;
	while (args[++i])
	{
		if (!control_expression(args[i]))
			return (update_env(node, envp), exit_message(NULL,
					"Error - Invalid usage.\n", 1), EXIT_FAILURE);
		if (ft_strchr(args[i], '='))
		{
			key = ft_trim(ft_strdup(args[i]), '=');
			if (!key)
				exit_allocation(node, NULL);
			envp = update_environment_variable(envp, key,
					ft_strdup(ft_strchr(args[i], '=') + 1));
			free(key);
			if (!envp)
				exit_allocation(node, NULL);
		}
	}
	return (update_env(node, envp), EXIT_SUCCESS);
}
