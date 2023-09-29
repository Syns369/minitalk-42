/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:22:24 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/29 19:04:39 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int		g_pause = 0;

void	send_char(int pid, unsigned char character)
{
	int				i;
	unsigned char	octet_tmp;

	octet_tmp = character;
	i = 8;
	while (i-- > 0)
	{
		octet_tmp = character >> i;
		if (octet_tmp % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_pause)
			usleep(1);
		g_pause = 0;
		// usleep(100);
	}
}

int	send_len(int pid, int len)
{
	int	i;
	int	bit;

	i = 31;
	while (i >= 0)
	{
		bit = (len >> i) & 1;
		if (bit == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_pause)
			usleep(1);
		g_pause = 0;
		// usleep(100);
		i--;
	}
	return (0);
}

void	receive_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		g_pause = 1;
		return ;
	}
	else if (signum == SIGUSR2)
	{
		g_pause = 1;
		ft_printf("Message received\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*message;
	int					i;
	int					message_len;
	struct sigaction	sa;

	sa.sa_handler = receive_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	if (argc != 3)
	{
		ft_printf("Usage: ./client [pid] [message]\n");
		exit(0);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	ft_printf("Sending message to %d\n", pid);
	message_len = ft_strlen(message);
	send_len(pid, message_len);
	i = 0;
	while (message[i])
	{
		send_char(pid, (unsigned char)message[i]);
		i++;
	}
	send_char(pid, (unsigned char) '\0');
	return (0);
}
