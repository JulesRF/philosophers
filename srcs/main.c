/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:54:53 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/03/29 17:13:11 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> ///////////////////////////////////////////////////////

int	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (1);
}

void	ft_putstr(char *str)
{
	write(1, &str, ft_strlen(str));
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			if (str[i] != '+')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_error(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_newphilo(t_data *data, int i;)
{
	t_philo		*philo;
	pthread_t	id;

	philo = malloc(sizeof(t_philo));
	//init philo

	pthread_create(&id, NULL, ft_routine, philo);
}

void	ft_init_philo(t_data *data, int argc, char **argv)
{
	int i;
	pthread_t	thread_id;
	t_philo		*philo;

	malloc(sizeof(t_philo *));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		ft_newphilo(data, i);
		i += 2;
	}
	i = 1
	while (i < argc)
	{
		ft_newphilo(data, i);
		i += 2;
	}
}

void	ft_init_struct(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -5;
	
}

void	*ft_test(void *arg)
{
	printf("salut\n");
	return (arg);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (ft_error(argc, argv))
		return (write(1, "Error\n", 6), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_init_struct(data, argc, argv);
	ft_init_philo(data, argc, argv);
	pthread_exit(NULL);
}