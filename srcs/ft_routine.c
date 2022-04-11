/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:03:23 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/11 17:04:11 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_status(t_philo *philo)
{
	if (ft_current_time() - philo->last_meal > philo->data->time_to_die
		&& philo->state == 1)
	{
		pthread_mutex_lock(&philo->data->ded);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->ded);
		philo->state = 0;
		ft_print_inf(philo, 4);
	}
	if (philo->data->dead == 1)
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	int		i;
	float	max;

	i = 0;
	max = (float)philo->data->time_to_sleep * 0.2;
	ft_print_inf(philo, 3);
	while (i < max)
	{
		if (ft_check_status(philo))
			return (1);
		usleep(5 * 1000);
		i++;
	}
	return (0);
}

int	ft_eat_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_tab[0]);
	ft_print_inf(philo, 1);
	pthread_mutex_lock(&philo->data->fork_tab[philo->index]);
	ft_print_inf(philo, 1);
	philo->last_meal = ft_current_time();
	ft_print_inf(philo, 5);
	if (ft_check_status(philo))
		return (1);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork_tab[philo->index]);
	pthread_mutex_unlock(&philo->data->fork_tab[0]);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->index == philo->data->nb_philo - 1)
	{
		if (ft_eat_last(philo))
			return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork_tab[philo->index]);
		ft_print_inf(philo, 1);
		pthread_mutex_lock(&philo->data->fork_tab[philo->index + 1]);
		ft_print_inf(philo, 1);
		philo->last_meal = ft_current_time();
		ft_print_inf(philo, 5);
		if (ft_check_status(philo))
			return (1);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->data->fork_tab[philo->index + 1]);
		pthread_mutex_unlock(&philo->data->fork_tab[philo->index]);
	}
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_meal == -5)
	{
		while (1)
		{
			if (ft_eat(philo) || ft_sleep(philo))
				return (NULL);
			ft_print_inf(philo, 2);
		}
	}
	else
	{
		while (philo->meals < philo->data->nb_meal)
		{
			ft_eat(philo);
			philo->meals++;
			if (philo->meals == philo->data->nb_meal)
				return (NULL);
			ft_sleep(philo);
			ft_print_inf(philo, 2);
		}
	}
	return (NULL);
}
