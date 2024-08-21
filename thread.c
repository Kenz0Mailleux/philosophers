/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:12:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/21 19:13:35 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(char *str, t_philo *philo)
{
	char	*time;

	time = get_time() - philo->data->time_start;
	printf("Philosopher %d %s\n",philo->nbr, str);
}


void	philo_eat(t_philo *philo)
{	
	pthread_mutex_lock(&philo->right_fork);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(&philo->left_fork);
	printf("philo %d\n", philo->nbr);
	print_state("has taken a fork", philo);
	print_state("is eating", philo);
	philo->last_meal = get_time();
	//new_sleep(philo->data->time_eat, philo->data);
	philo->meal++;
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}




void	eat_time(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo_eat(philo);
	// while (philo->data->death != 0 && philo->meal < philo->data->nbr_eat)
	// {
	// }
	
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