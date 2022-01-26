/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:57:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/01/26 20:06:32 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static long	ft_atol(const char	*str)
{
	long	nb;
	int		neg;

	nb = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		neg *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	return (neg * nb);
}

static void	ft_handler(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;
	write(1, "Bravo Jee\n", 10);
	exit(0);
}

static void	ft_error(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
	{
		write(1, "Usage : ./client <pid> <message>", 32);
		exit (1);
	}
	while (av[1][i])
	{
		if (av[1][i] < '0' || av[1][i] > '9')
		{
			write(1, "Please enter only digit\n", 24);
			exit (1);
		}
		else
			i++;
	}
	if (!av[1][0] || ft_atol(av[1]) == 0 || ft_atol(av[1]) >= INT_MAX)
	{	
		write(1, "PID is not valid", 16);
		exit (1);
	}
}

static void	ft_send_char(char av, int pid)
{
	int	i;
	int	ret;

	i = 7;
	ret = 0;
	while (i >= 0)
	{
		if ((av >> i) & 1)
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret)
		{
			write(1, "error signal\n", 13);
			exit(1);
		}
		usleep(30);
		i--;
	}
	usleep(80);
}

int	main(int ac, char **av)
{
	int					i;
	int					pid;
	struct sigaction	s2;

	ft_error(ac, av);
	i = 0;
	pid = ft_atol(av[1]);
	s2.sa_flags = SA_RESTART;
	s2.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &s2, NULL);
	while (av[2][i] != '\0')
	{
		ft_send_char(av[2][i], pid);
		i++;
	}
	ft_send_char(av[2][i], pid);
	while (1)
	{
	}
	return (0);
}
