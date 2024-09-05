/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:06:57 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:55:02 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*add_space(char *str, int i, t_node *node)
{
	int	length;

	length = ft_strlen(str);
	if (find_mark(str[i]) && (i + 1) < length && str[i + 1] != ' ')
		str = replace_str(str, i + 1, node);
	if (find_mark(str[i]) && (i - 1) >= 0 && str[i - 1] != ' ')
	{
		str = replace_str(str, i, node);
	}
	return (str);
}

char	*add_spaces(char *str, int i, t_node *node)
{
	int	length;

	length = ft_strlen(str);
	if ((i - 1) >= 0 && str[i - 1] != ' ')
	{
		str = replace_str(str, i, node);
		i++;
	}
	if ((i + 2) < length && str[i + 2] != ' ')
	{
		str = replace_str(str, i + 2, node);
		i++;
	}
	return (str);
}

int	change_space(char *str, char *new_str, int *i, int *j)
{
	if (find_mark(str[*i]) && str[*i - 2] == ' ')
	{
		new_str[*j - 1] = str[*i - 2];
		new_str[*j] = str[*i - 1];
		new_str[*j++] = str[*i++];
		return (1);
	}
	else if (find_mark(str[*i]) && str[*i + 1] == ' ')
	{
		new_str[*j++] = str[*i++];
		str[*i] = ' ';
		str[*i + 1] = '"';
		return (1);
	}
	return (0);
}

char	*replace_str(char *str, int index, t_node *node)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *) malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
	{
		exit_message(NULL, "Allocation error\n", 0);
		ft_exit(node, EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (index == i && !change_space(str, new_str, &i, &j))
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
		}
		else
			new_str[j++] = str[i++];
	}
	return (free(str), new_str[j] = 0, new_str);
}
