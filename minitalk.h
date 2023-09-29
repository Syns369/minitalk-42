/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:39:59 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/29 14:57:39 by jdarcour         ###   ########.fr       */
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

#endif