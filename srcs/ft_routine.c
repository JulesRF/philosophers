/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:03:23 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/22 17:00:25 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	ft_print_inf(philo, 3);
	if (ft_usleep(philo, philo->data->time_to_sleep))
		return (1);
	return (0);
}

int	ft_eat_last(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->data->fork_tab[0]);
		ft_print_inf(philo, 1);
		usleep(philo->data->time_to_die * 1000);
		ft_print_dead(philo);
		return (pthread_mutex_unlock(&philo->data->fork_tab[0]), 1);
	}
	pthread_mutex_lock(&philo->data->fork_tab[0]);
	if (ft_check_status(philo))
		return (pthread_mutex_unlock(&philo->data->fork_tab[0]), 1);
	ft_print_inf(philo, 1);
	pthread_mutex_lock(&philo->data->fork_tab[philo->index]);
	if (ft_check_status(philo))
		return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index]),
			pthread_mutex_unlock(&philo->data->fork_tab[0]), 1);
	ft_print_inf(philo, 1);
	ft_print_inf(philo, 5);
	philo->last_meal = ft_current_time();
	ft_usleep(philo, philo->data->time_to_eat);
	// if (ft_usleep(philo, philo->data->time_to_eat))
	// 	return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index]),
	// 		pthread_mutex_unlock(&philo->data->fork_tab[0]), 1);
	return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index]),
		pthread_mutex_unlock(&philo->data->fork_tab[0]), 0);
}

int	ft_eat(t_philo *philo)
{
	if (ft_check_status(philo) == 1)
		return (1);
	if (philo->index == philo->data->nb_philo - 1)
	{
		if (ft_eat_last(philo))
			return (1);
		return (0);
	}
	pthread_mutex_lock(&philo->data->fork_tab[philo->index]);
	if (ft_check_status(philo))
		return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index]), 1);
	ft_print_inf(philo, 1);
	pthread_mutex_lock(&philo->data->fork_tab[philo->index + 1]);
	if (ft_check_status(philo))
		return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index + 1]),
			pthread_mutex_unlock(&philo->data->fork_tab[philo->index]), 1);
	ft_print_inf(philo, 1);
	ft_print_inf(philo, 5);
	philo->last_meal = ft_current_time();
	ft_usleep(philo, philo->data->time_to_eat);
	// if (ft_usleep(philo, philo->data->time_to_eat))
	// 	return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index + 1]),
	// 		pthread_mutex_unlock(&philo->data->fork_tab[philo->index]), 1);
	return (pthread_mutex_unlock(&philo->data->fork_tab[philo->index + 1]),
		pthread_mutex_unlock(&philo->data->fork_tab[philo->index]), 0);
}

int	ft_inf_rout(t_philo *philo)
{
	while (1)
	{
		if (ft_eat(philo))
			return (1);
		if (ft_sleep(philo))
			return (1);
		ft_print_inf(philo, 2);
		usleep(200);
	}
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_meal == -5)
	{
		if (ft_inf_rout(philo))
			return (NULL);
	}
	else
	{
		while (philo->meals < philo->data->nb_meal)
		{
			if (ft_eat(philo))
				return (NULL);
			philo->meals++;
			if (philo->meals == philo->data->nb_meal)
				return (NULL);
			if (ft_sleep(philo))
				return (NULL);
			ft_print_inf(philo, 2);
			usleep(200);
		}
	}
	return (NULL);
}
