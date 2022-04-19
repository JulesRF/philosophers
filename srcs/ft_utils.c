/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:00:37 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/19 17:01:14 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// void	ft_putchar(char c)
// {
// 	write (1, &c, 1);
// }

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ded);
	if (philo->data->dead > 0)
		return (pthread_mutex_unlock(&philo->data->ded), 1);
	if ((ft_current_time() - philo->last_meal > philo->data->time_to_die)
		&& philo->state == 1)
	{
		philo->data->dead++;
		philo->state = 0;
		ft_print_dead(philo);
		return (pthread_mutex_unlock(&philo->data->ded), 1);
	}
	pthread_mutex_unlock(&philo->data->ded);
	return (0);
}

int	ft_usleep(t_philo *philo, long long time)
{
	int		i;
	float	max;

	i = 0;
	max = (float)time * 0.125;
	// if ((philo->last_meal + time) >= (ft_current_time() + (philo->data->time_to_die)))
	// {
	// 	usleep((ft_current_time() + (philo->data->time_to_die)) - ft_current_time());
	// 	return (1);
	// }
	while (i < max)
	{
		if (ft_check_status(philo))
			return (1);
		usleep(8 * 1000);
		i++;
	}
	return (0);
}
