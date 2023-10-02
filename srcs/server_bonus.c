/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:40:50 by jdarcour          #+#    #+#             */
/*   Updated: 2023/10/02 18:03:07 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	handle_sigint(char *buffer)
{
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
		data->buffer = (char *)malloc(sizeof(char) * (data->len + 1));
		if (!data->buffer)
		{
			free(data->buffer);
			data->buffer = NULL;
			return ;
		}
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
			ft_printf("Received message: %s\n\n", data->buffer);
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

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Usage: ./server\n");
		exit(0);
	}
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_printf("Error: sigaction failed\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_printf("Error: sigaction failed\n");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_printf("Error: sigaction failed\n");
	while (1)
		pause();
	return (0);
}
