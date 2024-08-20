/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:17 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/20 19:23:08 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int	init_philo(t_data data)
{
	t_philo	philo;

	philo->nbr = data

	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	data->number_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->nbr_eat = ft_atoi(argv[5]);
	data->lst =	malloc(t_philo * data->number_philo);
	while(i < data->number_philo)
	{
		data->philo_count = i
		pthread_create(data->lst[i], NULL, init_philo, data);
	}
}

int	main(int argc, char *argv[])
{
	t_data *data;

	if (!(argc == 5 || argc == 6) || init_data(argc, argv, data))
	{
		printf("Arguments non valide");
		return (1);
	}
	
	return (0);
}
