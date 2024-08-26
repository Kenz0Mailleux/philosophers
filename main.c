/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:17 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/26 16:17:34 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

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
	exit(0);
	return (0);
}
