/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:21:19 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/23 22:30:00 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				number_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	int				time_start;
	int				death;
	int				complete;
	int				ready;

	pthread_mutex_t	*print_m;
	pthread_mutex_t	*death_m;
	t_philo			*lst;
}					t_data;

typedef struct s_philo
{
	int				nbr;
	int				max_meal;
	int				eat_time;
	int				start_time;
	int				sleep_time;
	int				end;
	int				meal;
	long int		last_meal;

	pthread_t		thread_id;
	pthread_mutex_t	*meal_m;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
}					t_philo;

//fct utils
long	ft_atoi(char *str);
int		get_time(void);
int		ft_usleep(int time);

//philo
void	is_dead(t_data *data);
void	launch_thread(t_data *data);
void	*eat_time(void *arg);

//fct init et free
int		init_data(int argc, char **argv, t_data *data);
void	free_mutex(t_data *data);

#endif