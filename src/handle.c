/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:00:05 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/12/17 20:54:08 by muhaaydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <readline/readline.h>

extern int	g_pid;

void	kill_input(int signal)
{
	(void)signal;
	if (!g_pid)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		return ;
	}
	else
		kill(g_pid, SIGINT);
}
