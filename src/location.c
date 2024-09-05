/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:03:00 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 19:19:50 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <sys/stat.h>
#include <errno.h>

int	is_builtin(char *str)
{
	char	**builtin_func_list;
	int		i;

	builtin_func_list = (char **) malloc(sizeof(char *) * 8);
	builtin_func_list[0] = "cd";
	builtin_func_list[1] = "echo";
	builtin_func_list[2] = "pwd";
	builtin_func_list[3] = "export";
	builtin_func_list[4] = "unset";
	builtin_func_list[5] = "env";
	builtin_func_list[6] = "exit";
	builtin_func_list[7] = 0;
	i = 0;
	while (builtin_func_list[i])
	{
		if (!ft_strcmp(builtin_func_list[i], str))
			return (free(builtin_func_list), 1);
		i++;
	}
	return (free(builtin_func_list), 0);
}

int	control_executable(char *command)
{
	struct stat	buffer;

	if (stat(command, &buffer) == 0)
	{
		if (S_ISREG(buffer.st_mode) && buffer.st_mode & 0111)
			return (1);
		else
			return (0);
	}
	else
		errno = 0;
	return (0);
}

int	exist_directory(char *command)
{
	int	i;

	i = 0;
	while (command && command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*create_path(char *command, char *path_token)
{
	char	*file_path;

	file_path = ft_strjoin(path_token, "/");
	file_path = ft_strjoin(file_path, command);
	if (control_executable(file_path))
		return (file_path);
	free(file_path);
	return (NULL);
}

char	*get_location(char *command, char **envp, t_node *node)
{
	char	*path;
	char	*path_token;
	char	*file_path;

	if ((command && exist_directory(command) && control_executable(command))
		|| (command && is_builtin(command)))
		return (command);
	path = ft_getenv(envp, "PATH", node);
	if (command && path && *path)
	{
		path_token = ft_strtok(path, ":", node);
		while (path_token)
		{
			file_path = create_path(command, path_token);
			if (file_path)
				return (free(path), file_path);
			path_token = ft_strtok(path, ":", node);
		}
	}
	if (path)
		free(path);
	return (NULL);
}
