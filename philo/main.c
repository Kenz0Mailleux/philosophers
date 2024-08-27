/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:17 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/27 17:33:24 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void	print_state(char *str, t_philo *philo, int dead)
{
	int	time;

	(void)dead;
	if (!(philo->data->death))
	{
		pthread_mutex_lock(philo->data->print_m);
		time = get_time() - philo->start_time;
		printf("%d Philosopher %d %s\n", time, philo->nbr + 1, str);
		pthread_mutex_unlock(philo->data->print_m);
	}
}

void	launch_thread(t_data *data)
{
	int	i;

	i = -1;
	data->time_start = get_time();
	while (++i < data->number_philo)
	{
		data->lst[i].last_meal = data->time_start;
		pthread_create(&data->lst[i].thread_id,
			NULL, eat_time, &(data->lst[i]));
	}
	data->ready = 1;
	is_dead(data);
}

void	*one_philo(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	print_state("has taken right fork", &data->lst[0], 0);
	ft_usleep(data->time_die);
	print_state("died", &data->lst[0], 0);
	exit (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("Invalid arguments\n"), 1);
	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (printf("Invalid input"), 1);
		i++;
	}
	if (!init_data(argc, argv, &data))
		return (1);
	if (data.number_philo == 1)
		pthread_create(&data.lst[0].thread_id,
			NULL, eat_time, &(data.lst[0]));
	launch_thread(&data);
	i = 0;
	while (data.number_philo > 1 && i < data.number_philo)
	{
		pthread_join(data.lst[i].thread_id, NULL);
		i++;
	}
	return (free_mutex(&data), exit(0), 0);
}
