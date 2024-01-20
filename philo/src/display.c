/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:38:21 by lucas             #+#    #+#             */
/*   Updated: 2023/06/07 11:24:33 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(t_philo **philo, t_args *args, char *msg)
{
	int	i;

	i = -1;
	printf("%s\n", msg);
	if (args != NULL)
	{
		pthread_mutex_destroy(&args->mutex_eat);
		pthread_mutex_destroy(&args->print);
		pthread_mutex_destroy(&args->is_dead);
		free(args);
	}
	if (philo != NULL)
	{
		while (philo[++i])
			free(philo[i]);
	}
	exit(1);
}

void	ft_display(t_philo *philo, char *str)
{
	if (philo->args->dead == 1)
		return ;
	pthread_mutex_lock(&philo->args->print);
	if (philo->args->dead == 0)
		printf("%lli %d %s\n", ft_time() - philo->args->time, philo->index, str);
	pthread_mutex_unlock(&philo->args->print);
}

void	ft_to_free(t_philo **philo, t_args *args)
{
	int	i;

	i = -1;
	free(args);
	while (philo[++i])
		free(philo[i]);
	free(philo);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].args->nb_philo)
	{
		if (ft_current_time(philo[i].args->time)
			- philo[i].t_last_eat > philo[i].args->t_die)
		{
			pthread_mutex_lock(&philo[i].args->print);
			printf("%lli %d died\n",
				ft_time() - philo[i].args->time, philo[i].index);
			pthread_mutex_unlock(&philo[i].args->print);
			return (1);
		}
		i++;
	}
	return (0);
}
