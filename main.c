/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:17 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/21 20:46:22 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int	init_fork(t_data *data, int philo_nbr)
{
	data->lst[philo_nbr].right_fork = malloc(sizeof(pthread_mutex_t));
	if (!data->lst[philo_nbr].right_fork)
		exit(1);
	pthread_mutex_init(data->lst[philo_nbr].right_fork, NULL);
	if (data->lst[philo_nbr].nbr != 0)
		data->lst[philo_nbr].left_fork = (data)->lst[philo_nbr - 1].right_fork;
	if (data->lst[philo_nbr].nbr == data->number_philo - 1)
	{
		data->lst[0].left_fork = data->lst[philo_nbr].right_fork;
	}
	return 0;
	
}

int	init_philo(t_data *data, int philo_nbr)
{
	(data)->lst[philo_nbr].last_meal = 0;
	(data)->lst[philo_nbr].meal = 0;
	data->lst[philo_nbr].nbr = philo_nbr;
	data->lst[philo_nbr].time_start = 0;
	data->lst[philo_nbr].data = data;
	if (init_fork(data, philo_nbr) != 0)
		exit(1);
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->number_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	else 
		data->nbr_eat = 0;
	data->death = 0;
	data->lst =  malloc(sizeof(t_philo) * (data->number_philo + 1));
	if (!(data->lst))
		exit (1);
	while(i < data->number_philo)
	{
		init_philo(data, i);
		i++;
	}
	data->print_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->print_m, NULL);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data data;

	if (!(argc == 5 || argc == 6) || !init_data(argc, argv, &data))
	{
		printf("Arguments non valide");
		return (1);
	}
	launch_thread(&data);
	return (0);
}
