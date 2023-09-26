/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:22:24 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/26 18:27:46 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	send_message(int pid, char *message)
{
	(void)message;
	kill(pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [pid] [message]\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("Sending message to %d\n", pid);
	send_message(pid, argv[2]);
	return (0);
}
