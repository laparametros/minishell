/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaaydi <muhaaydi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:08:10 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 22:02:25 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**copy_array(char **array, int size)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!size)
	{
		while (array[i])
			i++;
		size = i;
	}
	new_array = (char **) malloc(sizeof(char *) * (size + 1));
	if (!new_array)
		return (NULL);
	i = -1;
	while (array[++i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (new_array[i] == NULL)
		{
			while (new_array[--i] != NULL)
				free(new_array[i]);
			return (NULL);
		}
	}
	return (new_array[i] = 0, new_array);
}

char	**delete_environment(char *key, char **envp)
{
	int		i;
	int		change_flag;
	char	*env_key;

	change_flag = 0;
	i = 0;
	while (envp[i] && !change_flag)
	{
		env_key = ft_trim(ft_strdup(envp[i]), '=');
		if (!change_flag && ft_strcmp(env_key, key) == 0)
		{
			free(envp[i]);
			envp[i] = " ";
			change_flag = 1;
			free(env_key);
			i--;
			break ;
		}
		free(env_key);
		i++;
	}
	while (envp[i] && envp[++i] && change_flag)
		envp[i] = envp[i + 1];
	return (envp);
}

int	unset(char **args, t_node *node)
{
	char	**envp;
	int		i;

	i = 0;
	envp = node->env;
	while (args[i])
		envp = delete_environment(args[i++], envp);
	update_env(node, envp);
	return (EXIT_SUCCESS);
}
