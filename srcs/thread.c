/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:12:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/26 16:17:54 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_state(char *str, t_philo *philo, int dead)
{
	int	time;

	(void)dead;
	pthread_mutex_lock(philo->data->print_m);
	if (!(philo->data->death))
	{
		time = get_time() - philo->start_time;
		printf("%d Philosopher %d %s\n", time, philo->nbr + 1, str);
	}
	pthread_mutex_unlock(philo->data->print_m);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state("has taken right fork", philo, 0);
	pthread_mutex_lock(philo->left_fork);
	print_state("has taken left fork", philo, 0);
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = get_time();
	print_state("is eating", philo, 0);
	ft_usleep(philo->eat_time);
	philo->meal++;
	pthread_mutex_unlock(philo->meal_m);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*eat_time(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (!(philo->data->ready))
		continue ;
	if ((philo->nbr % 2) == 1)
		ft_usleep((philo->eat_time / 2));
	while (!philo->data->death)
	{
		if (philo->max_meal == -1)
			;
		else if (!(philo->max_meal > i))
			break ;
		philo_eat(philo);
		print_state("is sleeping", philo, 0);
		ft_usleep(philo->sleep_time);
		print_state("is thinking", philo, 0);
		i++;
	}
	philo->end = 1;
	return (NULL);
}

int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(data->lst[i].meal_m);
	if ((get_time() - (data->lst[i].last_meal)) >= (data->time_die))
	{
		print_state("died \n\n", &data->lst[i], 1);
		data->death = 1;
		pthread_mutex_unlock(data->lst[i].meal_m);
		return (1);
	}
	pthread_mutex_unlock(data->lst[i].meal_m);
	return (0);
}
void	is_dead(t_data *data)
{
	int	i;
	int	j;
	int	max;

	max = data->nbr_eat;
	while (!(data->ready))
		continue ;
	while (1)
	{
		i = 0;
		while (i < data->number_philo)
		{
			if (max == -1)
				;
			else if (!(max > data->lst[i].meal))
				break ;
			if (check_death(data, i))
			{
				return;
			}
			i++;
		}
		data->complete = 1;
		j = 0;
		while (data->number_philo > j)
		{
			if (data->lst[j].end == 0)
				data->complete = 0;
			j++;
		}
		if (data->complete == 1)
			return ;
	}
}
