/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:57:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/01/23 16:38:16 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_print_pid(int pid)
{
	char	to_print;

	to_print = 0;
	if (pid >= 10)
		ft_print_pid(pid / 10);
	ft_putchar_fd((pid % 10) + 48, 1);
}

static void	ft_reset(char *s, int *i, int *byte, siginfo_t *info)
{
	kill(info->si_pid, SIGUSR1);
	s[0] = '\0';
	*i = 0;
	*byte = 0;
}

static void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static int	byte = 0;
	static int	i = 0;
	static char	s[INT_MAX];

	(void)context;
	if (byte == 0)
		s[i] = '\0';
	if (byte < 8)
	{
		s[i] = s[i] << 1;
		if (signal == SIGUSR2)
			s[i] = s[i] + 1;
		byte++;
	}
	if (byte == 8)
	{
		if (!s[i] || i == INT_MAX - 1)
		{
			write(1, s, i);
			ft_reset(s, &i, &byte, info);
			return ;
		}
		byte = 0;
		i++;
	}
}

int	main(void)
{
	struct sigaction	s1;

	s1.sa_flags = SA_RESTART;
	s1.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &s1, NULL);
	sigaction(SIGUSR2, &s1, NULL);
	write(1, "PID: ", 5);
	ft_print_pid(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
