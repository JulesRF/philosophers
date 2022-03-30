/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:54:53 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/03/30 15:34:05 by jroux-fo         ###   ########.fr       */
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
	return (i);
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
	}
	if (nb <= 9)
		ft_putchar(nb + 48);
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + 48);
	}
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

	if (argc <= 4 || argc >= 7)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_putstr("Le philo numero ");
	ft_putnbr(philo->index);
	write(1, "\n", 1);
	pthread_exit(NULL);
}

void	ft_newphilo(t_data *data, int i)
{
	t_philo		*philo;
	pthread_t	id;

	(void)data;
	philo = malloc(sizeof(t_philo));
	//init philo
	philo->index = i;
	philo->id = id;
	data->philo_tab[i] = philo;
	pthread_create(&id, NULL, ft_routine, philo);
}

void	ft_init_philo(t_data *data, int argc)
{
	int 		i;
	
	data->philo_tab = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo_tab)
		return ;
	i = 0;
	while (i < argc)
	{
		ft_newphilo(data, i);
		i += 2;
	}
	usleep(data->time_to_eat);
	i = 1;
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
	ft_init_philo(data, argc);
	pthread_exit(NULL);
}