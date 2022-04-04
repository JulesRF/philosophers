/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:54:53 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/04 16:08:20 by jroux-fo         ###   ########.fr       */
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
			return (1);
		i++;
	}
	return (0);
}

void	ft_print(char *str, t_data *data)
{
	pthread_mutex_lock(&data->str_lock);
	ft_putstr(str);
	pthread_mutex_unlock(&data->str_lock);
}

long long    ft_current_time(void)
{
    struct timeval    time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_timestamp(long int time, t_data *data)
{
	pthread_mutex_lock(&data->time_lock);
	ft_putnbr(time);
	// printf("%ld", time);
	write(1, " ", 1);
	pthread_mutex_unlock(&data->time_lock);
}

void	ft_print_inf(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	ft_timestamp(ft_current_time() - philo->data->start_time, philo->data);
	ft_putnbr(philo->index + 1);
	write(1, " ", 1);
	pthread_mutex_unlock(&philo->data->lock);
}

int	ft_check_status(t_philo *philo)
{
	if (philo->state == 1)
		return (0);
	ft_print_inf(philo);
	ft_putstr("died\n");
	return (1);
}

void	ft_sleep(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->time_to_sleep / 50)
	{
		ft_check_status(philo);
		usleep(50 * 1000);
		i++;
	}
}

void	ft_eat(t_philo *philo)
{
	int	id_2fork;
	struct timeval	time;

	if (philo->index == philo->data->nb_philo - 1)
		id_2fork = 0;
	else
		id_2fork = philo->index + 1;
	pthread_mutex_lock(&philo->data->fork_tab[philo->index]);
	ft_print_inf(philo);
	ft_print("has taken a fork\n", philo->data);
	pthread_mutex_lock(&philo->data->fork_tab[id_2fork]);
	ft_print_inf(philo);
	ft_print("has taken a fork\n", philo->data);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork_tab[philo->index]);
	pthread_mutex_unlock(&philo->data->fork_tab[id_2fork]);
	gettimeofday(&time, NULL);
	philo->last_meal = time.tv_usec;
	// ft_print_inf(philo);
	// ft_putstr("is done eating\n");
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_meal == -5)
	{
		while (1)
		{
			ft_eat(philo);
			ft_sleep(philo);
			ft_print_inf(philo);
			ft_print("is thinking\n", philo->data);
		}
	}
	else
	{
		while (philo->meals < philo->data->nb_meal)
		{
			ft_eat(philo);
			philo->meals++;
			ft_sleep(philo);
			ft_print_inf(philo);
			ft_print("is thinking\n", philo->data);
		}
	}
	pthread_exit(NULL);
}

void	ft_newphilo(t_data *data, int i)
{
	t_philo		*philo;
	struct timeval	time;
	pthread_t	id;

	// id = NULL;
	philo = malloc(sizeof(t_philo));
	philo->index = i;
	philo->state = 1;
	philo->meals = 0;
	philo->id = id;
	philo->data = data;
	gettimeofday(&time, NULL);
	philo->last_meal = time.tv_usec;
	data->philo_tab[i] = philo;
	pthread_create(&id, NULL, ft_routine, philo);
}

void	ft_init_philo(t_data *data, int argc)
{
	int 			i;
	
	(void)argc;
	data->philo_tab = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo_tab)
		return ;
	i = 0;
	data->start_time = ft_current_time();
	while (i < data->nb_philo)
	{
		ft_newphilo(data, i);
		i += 2;
	}
	usleep(20);
	i = 1;
	while (i < data->nb_philo)
	{
		ft_newphilo(data, i);
		i += 2;
	}
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
	if (argc == 6)
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -5;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->str_lock, NULL);
	pthread_mutex_init(&data->time_lock, NULL);
	data->philo_tab = malloc(sizeof(t_philo) * data->nb_philo);
	ft_init_fork(data);
}

// int  ft_join(pthread_t *tab_de_threads, t_data *data)
// {
//     int  i;
	
// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		pthread_join(tab_de_threads[i]->id, NULL);
// 		i++;
// 	}
// 	return (0);
// }

void	ft_clean_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork_tab[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->str_lock);
	pthread_mutex_destroy(&data->time_lock);
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
	// ft_join(data->philo_tab, data);
	ft_clean_mutex(data);
	pthread_exit(NULL);
}