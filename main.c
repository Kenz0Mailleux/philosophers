/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:17 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/23 22:01:05 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_fork(t_data *data, int philo_nbr)
{
	data->lst[philo_nbr].right_fork = malloc(sizeof(pthread_mutex_t));
	if (!data->lst[philo_nbr].right_fork)
		exit(1);
	pthread_mutex_init(data->lst[philo_nbr].right_fork, NULL);
	if (data->lst[philo_nbr].nbr != 0)
		data->lst[philo_nbr].left_fork = data->lst[philo_nbr - 1].right_fork;
	if (data->lst[philo_nbr].nbr == data->number_philo - 1)
		data->lst[0].left_fork = data->lst[philo_nbr].right_fork;
	data->lst[philo_nbr].meal_m = malloc(sizeof(pthread_mutex_t));
	if (!data->lst[philo_nbr].meal_m)
		exit(1);
	pthread_mutex_init(data->lst[philo_nbr].meal_m, NULL);
	return (0);
}

int	init_philo(t_data *data, int philo_nbr)
{
	data->lst[philo_nbr].last_meal = 0;
	data->lst[philo_nbr].meal = 0;
	data->lst[philo_nbr].max_meal = data->nbr_eat;
	data->lst[philo_nbr].sleep_time = data->time_sleep;
	data->lst[philo_nbr].start_time = data->time_start;
	data->lst[philo_nbr].end = 0;
	data->lst[philo_nbr].nbr = philo_nbr;
	data->lst[philo_nbr].data = data;
	data->lst[philo_nbr].eat_time = data->time_eat;
	if (init_fork(data, philo_nbr) != 0)
		exit(1);
	data->lst[philo_nbr].last_meal = data->time_start;
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = -1;
	data->number_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->nbr_eat = -1;
	if (argc == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	data->time_start = get_time();
	data->death = 0;
	data->lst = malloc(sizeof(t_philo) * data->number_philo);
	if (!data->lst)
		exit(1);
	while (++i < data->number_philo)
		init_philo(data, i);
	data->print_m = malloc(sizeof(pthread_mutex_t));
	data->death_m = malloc(sizeof(pthread_mutex_t));
	if (!data->print_m || !data->death_m)
		exit(1);
	pthread_mutex_init(data->print_m, NULL);
	return (pthread_mutex_init(data->death_m, NULL), 1);
}

void	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(data->lst[i].right_fork);
		pthread_mutex_destroy(data->lst[i].meal_m);
		free(data->lst[i].right_fork);
		free(data->lst[i].meal_m);
		i++;
	}
	pthread_mutex_destroy(data->print_m);
	pthread_mutex_destroy(data->death_m);
	free(data->print_m);
	free(data->death_m);
	free(data->lst);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	if (!init_data(argc, argv, &data))
		return (1);
	launch_thread(&data);
	i = 0;
	while (i < data.number_philo)
	{
		pthread_join(data.lst[i].thread_id, NULL);
		i++;
	}
	free_mutex(&data);
	return (0);
}
