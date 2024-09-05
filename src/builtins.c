/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaaydi <muhaaydi@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:53:24 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:43:30 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int	control_directory(char *dir)
{
	if (!access(dir, F_OK))
	{
		if (access(dir, X_OK))
		{
			exit_message(NULL, "Permission denied!\n", 1);
			return (0);
		}
		return (1);
	}
	exit_message(NULL, "No such file or directory\n", 1);
	return (0);
}

int	is_directory(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
		return (-1);
	if (S_ISDIR(file_stat.st_mode))
		return (1);
	else
		return (0);
}

int	env(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	echo(char **args)
{
	int	i;
	int	j;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		newline_flag = 0;
		i++;
	}
	if (!args[i])
		return (printf("\n"), EXIT_SUCCESS);
	j = i;
	while (args[i])
	{
		if (i != j)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (newline_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	cd(char **args)
{
	if (!args[1])
		printf("\n");
	else if (args[2])
	{
		exit_message(NULL, "Error! too many arguments\n", 1);
		return (EXIT_FAILURE);
	}
	else if (args[1])
	{
		if (control_directory(args[1]) && is_directory(args[1]))
			chdir(args[1]);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
