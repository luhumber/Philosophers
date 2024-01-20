/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:33:11 by lucas             #+#    #+#             */
/*   Updated: 2023/06/07 11:35:24 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_eat(t_philo *philo, t_args *args)
{
	ft_display(philo, "is eating");
	if (args->dead == 1)
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), -1);
	pthread_mutex_lock(&philo->args->mutex_eat);
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->args->mutex_eat);
	ft_usleep(args->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (args->dead == 1)
		return (-1);
	ft_display(philo, "is sleeping");
	ft_usleep(args->t_sleep);
	if (args->dead == 1)
		return (-1);
	ft_display(philo, "is thinking");
	return (0);
}

int	ft_take_fork(t_philo *philo, t_args *args)
{
	if (args->dead == 1)
		return (-1);
	pthread_mutex_lock(&philo->l_fork);
	ft_display(philo, "has taken a fork");
	if (args->nb_philo == 1)
		return (pthread_mutex_unlock(&philo->l_fork),
			ft_usleep(args->t_die + 2), -1);
	if (args->dead == 1)
		return (pthread_mutex_unlock(&philo->l_fork), -1);
	pthread_mutex_lock(philo->r_fork);
	ft_display(philo, "has taken a fork");
	return (0);
}

void	is_dead(t_philo *philo, t_args *args)
{
	int	nb_eat;

	nb_eat = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->args->is_dead);
		if (check_if_dead(philo) == 1)
		{
			args->dead = 1;
			pthread_mutex_unlock(&philo->args->is_dead);
			break ;
		}
		if (args->must_eat != -1 && nb_eat >= args->must_eat)
		{
			args->dead = 1;
			pthread_mutex_unlock(&philo->args->is_dead);
			break ;
		}
		nb_eat++;
		pthread_mutex_unlock(&philo->args->is_dead);
	}
}

void	ft_routine_loop(t_philo *philo, t_args *args)
{
	while (args->dead == 0)
	{
		if (ft_take_fork(philo, args) == -1)
			return ;
		if (ft_eat(philo, args) == -1)
			return ;
	}
	return ;
}

void	*ft_philo(void *s_philo)
{
	t_philo		*philo;
	t_args		*args;

	philo = (t_philo *)s_philo;
	args = (t_args *)philo->args;
	pthread_mutex_lock(&philo->args->execution_lock);
	pthread_mutex_unlock(&philo->args->execution_lock);
	philo->args->time = ft_time();
	philo->t_last_eat = philo->args->time;
	if (philo->index % 2 == 0)
		ft_usleep(1);
	ft_routine_loop(philo, args);
	return (NULL);
}
