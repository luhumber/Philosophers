/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:08:37 by lucas             #+#    #+#             */
/*   Updated: 2023/06/07 11:19:22 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_create_philo(t_args *args)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * args->nb_philo);
	if (!philo)
		ft_error(NULL, args, "Error malloc");
	i = -1;
	pthread_mutex_lock(&args->execution_lock);
	while (++i < args->nb_philo)
	{
		philo[i].args = args;
		philo[i].index = i + 1;
		philo[i].t_last_eat = 0;
		philo[i].nb_eat = 0;
		pthread_mutex_init(&philo[i].l_fork, NULL);
		if (i != args->nb_philo - 1)
			philo[i].r_fork = &philo[i + 1].l_fork;
		else
			philo[i].r_fork = &philo[0].l_fork;
		if (pthread_create(&philo[i].thread, NULL, ft_philo, &philo[i]))
			ft_error(&philo, args, "Thread Error");
	}
	pthread_mutex_unlock(&args->execution_lock);
	is_dead(philo, args);
	i = -1;
	while (++i <= args->nb_philo)
		pthread_join(philo[i].thread, NULL);
	free(philo);
}

t_args	*ft_init_args(int argc, char **argv)
{
	t_args	*args;
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	args = malloc(sizeof(t_args));
	if (!args)
		ft_error(NULL, args, "Error malloc");
	args->nb_philo = nb_philo;
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->dead = 0;
	args->time = ft_time();
	pthread_mutex_init(&args->execution_lock, NULL);
	pthread_mutex_init(&args->mutex_eat, NULL);
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->is_dead, NULL);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
	return (args);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("The number of arguments is not correct\n"), 1);
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '-')
			return (printf("No negative numbers\n"), 1);
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (printf("It's not a digit\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	if (ft_check_args(argc, argv) == 1)
		return (1);
	args = ft_init_args(argc, argv);
	ft_create_philo(args);
	free(args);
	return (0);
}
