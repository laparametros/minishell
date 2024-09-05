/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:08:25 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 19:09:58 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <fcntl.h>
#include <errno.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (s2[i]);
	if (!s2 && s1)
		return (s1[i]);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	null_to_array(char **array, int length)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < length)
		array[i++] = NULL;
}

int	file_exist(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd == -1 && errno == ENOENT)
	{
		exit_message(NULL, "Error: ", 0);
		exit_message(file, " file doesn't exist\n", 0);
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 && errno == EACCES)
	{
		exit_message(NULL, "Error: permission denied!\n", 0);
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 && errno == EISDIR)
	{
		exit_message(NULL, "Error: ", 0);
		exit_message(file, " is a directory\n", 0);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	file_exist_writing(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && errno == ENOENT)
	{
		exit_message(NULL, "Error: ", 0);
		exit_message(file, " file doesn't exist\n", 0);
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 && errno == EACCES)
	{
		exit_message(NULL, "Error: permission denied!\n", 0);
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 && errno == EISDIR)
	{
		exit_message(NULL, "Error: ", 0);
		exit_message(file, " is a directory\n", 0);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	file_exist_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1 && errno == ENOENT)
	{
		exit_message(NULL, "Error: ", 0);
		exit_message(file, " file doesn't exist\n", 0);
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 && errno == EACCES)
	{
		exit_message(NULL, "Error: permission denied!\n", 0);
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 && errno == EISDIR)
	{
		exit_message(NULL, "Error: ", 0);
		exit_message(file, " is a directory\n", 0);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
