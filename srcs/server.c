/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:40:50 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/28 19:07:46 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"


void	handler(int signum)
{
	static unsigned int		len;
	static unsigned int		bit_count = 0;
	static unsigned char	current_char;
	static int				i;
	static char				*buffer;

	if (signum == SIGINT)
	{
		ft_printf("Received SIGINT\n");
		if (buffer)
			free(buffer);
		exit(0);
	}
	if (bit_count < 31)
	{
		len <<= 1;
		len |= (signum == SIGUSR1);
		bit_count++;
	}
	else if (bit_count == 31)
	{
		len <<= 1;
		len |= (signum == SIGUSR1);
		ft_printf("Received length: %u\n", len);
		buffer = (char *)malloc(sizeof(char) * (len + 1));
		buffer[0] = '\0';
		bit_count++;
	}
	else
	{
		current_char |= (signum == SIGUSR1);
		i++;
		if (i == 8)
		{
			if (current_char == '\0')
			{
				ft_printf("Received message: %s\n", buffer);
				free(buffer);
				buffer = NULL;
				bit_count = 0;
				len = 0;
				current_char = 0;
				i = 0;
			}
			else
			{
				ft_strlcat(buffer, (const char*) &current_char, len + 1);
				i = 0;
				current_char = 0;
			}
		}
		else
			current_char <<= 1;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		pause();
	return (0);
}
