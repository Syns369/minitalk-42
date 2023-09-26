/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:40:50 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/26 18:38:22 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	handler(int signum)
{
	(void)signum;
	write(1, "Signal received\n", 16);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;

	sigaction(SIGUSR1, &sa, NULL);
	ft_printf("My pid is %d\n", getpid());
	while (1)
		pause();
	return (0);
}
