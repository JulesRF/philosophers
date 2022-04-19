/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:06:29 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/19 13:51:30 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo_tab[i]->id, NULL);
		free(data->philo_tab[i]);
		i++;
	}
	free(data->philo_tab);
	return (0);
}

void	ft_clean_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork_tab[i]);
		i++;
	}
	free(data->fork_tab);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->ded);
	pthread_mutex_destroy(&data->print_dead);
}
