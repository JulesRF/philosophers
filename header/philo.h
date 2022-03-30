/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:03:19 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/03/30 15:26:36 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_data	t_data;

typedef struct	s_philo {
	int			index;
	pthread_t	id;
	t_data		*data;
}				t_philo;

typedef struct	s_data {
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_meal;
	int			*tab;
	t_philo		**philo_tab;
	t_philo		*philo;
}				t_data;

int ft_strlen(const char *str);

//	ft_atoi.c
int	ft_atoi(const char *nptr);

#endif