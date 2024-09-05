/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:58:25 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 15:42:54 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;
	int	length;

	if (!s1 || !s2 || !*s1 || !*s2)
		return (NULL);
	i = 0;
	length = ft_strlen(s1);
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	while (i < length)
		s1[i++] = 0;
	return (s1);
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*str;

	len = ft_strlen(src);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	while (--len >= 0)
		str[len] = src[len];
	return (str);
}

int	delim_control(char *str, char *delim, int flag)
{
	int	j;
	int	i;
	int	k;

	if (!str || !*str || !delim || !*delim)
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		k = 0;
		while (delim[j])
		{
			if (str[i] == delim[j++])
				k = 1;
		}
		if ((!flag && k) || (flag && !k))
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtok(char *str, char *delim, t_node *node)
{
	char	*result;
	char	*copy_str;
	int		i;
	int		j;
	int		start;

	if (!str || !delim || !*str || !delim)
		return (NULL);
	j = -1;
	start = delim_control(str, delim, 1);
	i = delim_control(&str[start], delim, 0);
	if (!str[start])
		return (NULL);
	copy_str = ft_strdup(&str[start]);
	result = (char *) malloc(sizeof(char) * (i + 1));
	if (!copy_str || !result)
		exit_allocation(node, copy_str);
	while (++j < i && copy_str[j])
		result[j] = copy_str[j];
	result[j] = 0;
	if (copy_str[i])
		str = ft_strcpy(str, &copy_str[i]);
	else
		str[0] = '\0';
	return (free(copy_str), result);
}
