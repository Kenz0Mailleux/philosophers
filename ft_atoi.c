/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:00:39 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/21 17:46:38 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

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
