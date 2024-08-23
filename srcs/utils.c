/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:20:42 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/23 22:25:20 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <limits.h>

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

static int	sign_space(char *str, int *ptr_len)
{
	int	sign;
	int	len;

	len = 0;
	sign = 1;
	while ((str[len] >= 9 && str[len] <= 13) || str[len] == 32)
		len++;
	if (str[len] && (str[len] == 43 || str[len] == 45))
	{
		if (str[len] == '-')
			sign *= -1;
		len++;
	}
	*ptr_len = len;
	return (sign);
}

long	ft_atoi(char *str)
{
	int					sign;
	unsigned long int	result;
	int					len;
	int					len_nb;

	result = 0;
	sign = sign_space(str, &len);
	len_nb = len;
	while (str[len] && str[len] == '0')
		len++;
	while (str[len] && str[len] >= 48 && str[len] <= 57)
	{
		result *= 10;
		result += str[len] - '0';
		len++;
		len_nb++;
		if (result > (unsigned)LONG_MAX)
		{
			if (sign > 0)
				return (21474836471);
			if (sign < 0)
				return (21474836471);
		}
	}
	return ((long)result * sign);
}
