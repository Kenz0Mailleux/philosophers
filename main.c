/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:17 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/20 22:48:33 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	*init_philo(void *arg)
{
	t_data	*data;

	data = (t_data *)(arg);
	data->lst[data->philo_count].nbr = data->philo_count;
	data->lst[data->philo_count].meal = 0;
	// data->lst[data->philo_count].last_meal = 0;
	// data->lst[data->philo_count].time_start = 0;
	//data->lst[data->philo_count].right_fork = init_mutex;
	// if ((data->lst[(data->philo_count) - 1].right_fork))
	// 	//si last philo compare au premier
	// 	if ((data->philo_count + 1) == data->number_philo)
	// 		data->lst[data->philo_count].left_fork = init_mutex;
	// 	//autrement tqt
	// 	else
	// 		data->lst[data->philo_count].left_fork = data->lst[data->philo_count-1].right_fork;
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;
	pthread_t* thread_lst;

	i = 0;
	data->number_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	data->death = 0;
	data->lst =  malloc(sizeof(t_philo) * data->number_philo);
	if (!(data->lst))
		exit (1);
	while(i < data->number_philo)
	{
		data->philo_count = i;
		if (pthread_create(&(data->lst[i].thread_id), NULL, init_philo, data))
			exit (1);
		ft_usleep(20);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data *data;

	data = malloc(sizeof (data) * 1);
	if (!(argc == 5 || argc == 6) || !init_data(argc, argv, data))
	{
		printf("Arguments non valide");
		return (1);
	}

	printf("%d", data->lst[3].nbr);
	return (0);
}
