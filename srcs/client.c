/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:22:24 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/29 15:25:35 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

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
		usleep(100);
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
		usleep(100);
		i--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;
	int		message_len;

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
	// usleep(100);
	i = 0;
	while (message[i])
	{
		send_char(pid, (unsigned char)message[i]);
		i++;
	}
	// send_char(pid, (unsigned char) '\n');
	send_char(pid, (unsigned char) '\0');
	return (0);
}
