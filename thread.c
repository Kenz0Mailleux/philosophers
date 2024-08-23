/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:12:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/23 18:22:07 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(char *str, t_philo *philo, int dead)
{
	int	time;

	pthread_mutex_lock(philo->data->print_m);
	time = get_time() - philo->start_time;
	printf("%d Philosopher %d %s\n",time, philo->nbr + 1, str);
	if (!dead)
		pthread_mutex_unlock(philo->data->print_m);
}

void	philo_eat(t_philo *philo)
{	
	pthread_mutex_lock(philo->right_fork);
	print_state("has taken right fork", philo, 0);
	pthread_mutex_lock(philo->left_fork);
	print_state("has taken left fork", philo, 0);
	print_state("is eating", philo, 0);
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = get_time();
	ft_usleep(philo->eat_time);
	philo->meal++;
	pthread_mutex_unlock(philo->meal_m);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


void	is_dead(t_data	*data)
{
	int	i;
	int	j;
	int	time;

	i = 0;
	time = get_time();
	while (!data->death)
	{
		i = 0;
		//lancer quand tout est en marche
		while (i < data->number_philo && !data->death && data->lst[i].max_meal > data->lst[i].meal)
		{
			if ((get_time() - (data->lst[i].last_meal)) > (data->time_die))
			{
				pthread_mutex_lock(data->death_m);
				print_state("died \n", &data->lst[i], 1);
				data->death = 1;
				pthread_mutex_unlock(data->death_m);
				return ;
			}
			i++;
		}
		j = 0;
		data->complete = 1;
		while(data->number_philo > j)
		{
			if (data->lst[j].end == 0)
				data->complete = 0;
			j++;
		}
		if (data->complete == 1)
			return ;
	}
	i = 0;
	j = data->number_philo;
	while (i < j)
	{
		pthread_join(data->lst[i].thread_id, NULL);
		i++;
	}
}



void	*eat_time(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if ((philo->nbr % 2) == 1)
		ft_usleep(philo->eat_time);
	while (philo->max_meal > i++)
	{
		philo_eat(philo);
		print_state("is sleeping", philo, 0);
		ft_usleep(philo->sleep_time);
		print_state("is thinking", philo, 0);
	}
	philo->end = 1;
	return (NULL);
}

void	launch_thread(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = data->number_philo;
	data->time_start = get_time();
	while(++i < j)
	{
		data->lst[i].last_meal = data->time_start;
		pthread_create(&data->lst[i].thread_id, NULL, eat_time, &(data->lst[i]));
	}	
	is_dead(data);
	exit (0);
}
