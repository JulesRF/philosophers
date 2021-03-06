/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:04:38 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/25 15:48:06 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_newphilo(t_data *data, int i)
{
	t_philo			*philo;
	pthread_t		id;

	philo = malloc(sizeof(t_philo));
	philo->index = i;
	philo->state = 1;
	philo->meals = 0;
	philo->data = data;
	philo->last_meal = ft_current_time();
	data->philo_tab[i] = philo;
	pthread_create(&id, NULL, ft_routine, philo);
	philo->id = id;
}

void	ft_monitoring(t_data *data, int i, int meal)
{
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (meal == data->nb_meal)
				return ;
			pthread_mutex_lock(&data->last_meal);
			if (data->philo_tab[i]->meals == data->nb_meal)
				meal++;
			else if (ft_current_time() - data->philo_tab[i]->last_meal
				> data->time_to_die)
			{
				pthread_mutex_unlock(&data->last_meal);
				pthread_mutex_lock(&data->ded);
				data->dead++;
				ft_print_dead(data->philo_tab[i]);
				pthread_mutex_unlock(&data->ded);
				return ;
			}
			pthread_mutex_unlock(&data->last_meal);
			i++;
		}
		usleep(1000);
	}
}

void	ft_init_philo(t_data *data, int argc)
{
	int	i;

	(void)argc;
	i = 0;
	data->start_time = ft_current_time();
	while (i < data->nb_philo)
	{
		ft_newphilo(data, i);
		i += 2;
	}
	usleep(data->time_to_eat * 1000);
	i = 1;
	while (i < data->nb_philo)
	{
		ft_newphilo(data, i);
		i += 2;
	}
	if (data->nb_philo != 1)
		ft_monitoring(data, 0, 0);
}

void	ft_init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fork_tab = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork_tab[i], NULL);
		i++;
	}
}

void	ft_init_struct(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argc == 6)
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -5;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->ded, NULL);
	pthread_mutex_init(&data->last_meal, NULL);
	data->philo_tab = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo_tab)
		return ;
	ft_init_fork(data);
}
