/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:12:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/21 21:26:38 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(char *str, t_philo *philo)
{
	int	time;

	time = get_time() - philo->data->time_start;
	pthread_mutex_lock(philo->data->print_m);
	printf("%d Philosopher %d %s\n",time, philo->nbr, str);
	pthread_mutex_unlock(philo->data->print_m);
}

void	philo_eat(t_philo *philo)
{	
	pthread_mutex_lock(philo->right_fork);
	print_state("has taken right fork", philo);
	pthread_mutex_lock(philo->left_fork);
	print_state("has taken left fork", philo);
	print_state("is eating", philo);
	philo->last_meal = get_time();
	usleep(philo->data->time_eat);
	write(1, "x", 1);
	//new_sleep(philo->data->time_eat, philo->data);
	philo->meal++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*eat_time(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	write(1, "x", 1);
	if ((philo->nbr % 2) == 0)
		usleep(philo->data->time_eat / 2);
	while (philo->data->death == 0 || philo->data->nbr_eat > philo->meal)
	{
		philo_eat(philo);
		print_state("is sleeping", philo);
		usleep(philo->data->time_sleep);
		print_state("is thinking", philo);
	}
	return (NULL);
}

void	launch_thread(t_data *data)
{
	int	i;

	i = 0;
	data->time_start = get_time();
	while(i < data->number_philo)
	{
		data->lst[i].last_meal = get_time();
		if (pthread_create(&data->lst[i].thread_id, NULL, eat_time, &(data->lst[i])))
		 	exit (0);
		i++;
	}	
}
