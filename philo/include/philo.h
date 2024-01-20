/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:01:48 by lucas             #+#    #+#             */
/*   Updated: 2023/06/06 17:13:57 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_args {
	long long int	time;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				fork;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	execution_lock;
	int				dead;
}	t_args;

typedef struct s_philo {
	t_args			*args;
	int				index;
	long long int	t_last_eat;
	int				nb_eat;
	pthread_mutex_t	l_fork;
	bool			l_fork_locked;
	pthread_mutex_t	*r_fork;
	bool			r_fork_locked;
	pthread_t		thread;
	pthread_t		died;
}	t_philo;

void			*ft_philo(void *s_philo);
long long int	ft_time(void);
long long int	ft_current_time(long long int time);
void			ft_usleep(int ms);
int				ft_atoi(const char *str);
void			ft_error(t_philo **philo, t_args *args, char *msg);
void			ft_to_free(t_philo **philo, t_args *args);
void			ft_display(t_philo *philo, char *str);
int				check_if_dead(t_philo *philo);
void			is_dead(t_philo *philo, t_args *args);

#endif