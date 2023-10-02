/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:39:59 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/30 15:47:18 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft-42/libft.h"

# include <signal.h>
# include <unistd.h>

typedef struct s_data
{
	unsigned int	len;
	unsigned int	bit_count;
	unsigned char	c;
	int				i;
	char			*buffer;
}				t_data;

void			handle_sigint(char *buffer);
void			handle_length(t_data *data, int signum);
void			handle_message(t_data *data, int signum, siginfo_t *info);
void			handler(int signum, siginfo_t *info, void *context);

void			receive_handler(int signum);
void			send_char(int pid, unsigned char character);
int				send_len(int pid, int len);
void			send_message(int pid, char *message);

#endif