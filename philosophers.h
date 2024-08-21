/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:21:19 by kmailleu          #+#    #+#             */
/*   Updated: 2024/08/21 20:45:08 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_PHILO_H
# define SO_PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo t_philo;

typedef struct s_data
{
	int				number_philo;
	int				time_die;
	int 			time_eat;
	int				time_sleep;
	int 			nbr_eat;
	int				time_start;
	int				death;
	int				philo_count;

	pthread_mutex_t	*print_m;
	pthread_mutex_t	*death_m;
	t_philo 		*lst;
}					t_data;


typedef struct	s_philo
{
	int				nbr;
	int				meal;
	long int		last_meal;
	long int		time_start;

	pthread_t		thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
}					t_philo;

long	ft_atoi(char *str);
int		ft_usleep(int time);
void	launch_thread(t_data *data);
int		get_time();

#endif