/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:54:53 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/03/28 17:05:37 by jroux-fo         ###   ########.fr       */
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

void	*ft_init_philo()
{
	int i;
}

void	ft_init_struct(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meal = argv[5];
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
	pthread_t id;
	
	t_data	*data;
	if (ft_error(argc, argv))
		return (write(1, "Error\n", 6), 1);
	ft_init_struct(data, argc, argv);
	pthread_create(&id, NULL, ft_test, (void *)&id);
	pthread_exit(NULL);
}