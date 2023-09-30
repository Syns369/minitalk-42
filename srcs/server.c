/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:40:50 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/30 12:51:10 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	handle_sigint(char *buffer)
{
	ft_printf("Received SIGINT\n");
	if (buffer)
		free(buffer);
	exit(0);
}

void	handle_length(t_data *data, int signum)
{
	if (data->bit_count < 31)
	{
		data->len <<= 1;
		data->len |= (signum == SIGUSR1);
		(data->bit_count)++;
	}
	else if (data->bit_count == 31)
	{
		data->len <<= 1;
		data->len |= (signum == SIGUSR1);
		ft_printf("Received length: %u\n", data->len);
		data->buffer = (char *)malloc(sizeof(char) * (data->len + 1));
		data->buffer[0] = '\0';
		(data->bit_count)++;
	}
}

void	handle_message(t_data *data, int signum, siginfo_t *info)
{
	data->c |= (signum == SIGUSR1);
	data->i++;
	if (data->i == 8)
	{
		if (data->c == '\0')
		{
			ft_printf("Received message: %s\n", data->buffer);
			kill(info->si_pid, SIGUSR2);
			free(data->buffer);
			data->buffer = NULL;
			data->bit_count = 0;
			data->len = 0;
			data->c = 0;
			data->i = 0;
		}
		else
		{
			ft_strlcat(data->buffer, (const char *) &data->c, data->len + 1);
			data->i = 0;
			data->c = 0;
		}
	}
	else
		data->c <<= 1;
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static t_data	data;

	(void)context;
	if (signum == SIGINT)
		handle_sigint(data.buffer);
	if (data.bit_count < 32)
		handle_length(&data, signum);
	else
		handle_message(&data, signum, info);
	if (signum == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signum == SIGUSR2)
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		pause();
	return (0);
}
