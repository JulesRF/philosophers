/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:05:50 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/25 15:36:24 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

char	*ft_display_string(int wich)
{
	if (wich == 1)
		return ("has taken a fork\n");
	if (wich == 2)
		return ("is thinking\n");
	if (wich == 3)
		return ("is sleeping\n");
	if (wich == 4)
		return ("died\n");
	if (wich == 5)
		return ("is eating\n");
	return ("");
}

char	*ft_display_color(int wich)
{
	if (wich == 1)
		return ("\033[95m");
	if (wich == 2)
		return ("\033[36m");
	if (wich == 3)
		return ("\e[38;5;118m");
	if (wich == 4)
		return ("\e[38;5;196m");
	if (wich == 5)
		return ("\033[33m");
	return ("\033[95m");
}

void	ft_print_inf(t_philo *philo, int str)
{
	pthread_mutex_lock(&philo->data->ded);
	if (philo->data->dead > 0)
	{
		pthread_mutex_unlock(&philo->data->ded);
		return ;
	}
	pthread_mutex_lock(&philo->data->lock);
	ft_putstr(ft_display_color(str));
	printf("%lld %d %s", ft_current_time() - philo->data->start_time,
		philo->index + 1, ft_display_string(str));
	ft_putstr("\033[0m");
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->ded);
}

void	ft_print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead > 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return ;
	}
	ft_putstr("\e[38;5;196m");
	printf("%lld %d died\n", ft_current_time() - philo->data->start_time,
		philo->index + 1);
	ft_putstr("\033[0m");
	pthread_mutex_unlock(&philo->data->lock);
}
