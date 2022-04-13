/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:03:19 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/13 16:59:48 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo {
	int			index;
	int			state;
	int			meals;
	long long	last_meal;
	pthread_t	id;
	t_data		*data;
}				t_philo;

typedef struct s_data {
	int					nb_philo;
	double				time_to_die;
	double				time_to_eat;
	double				time_to_sleep;
	int					nb_meal;
	int					*tab;
	int					dead;
	long long			start_time;
	pthread_mutex_t		lock;
	pthread_mutex_t		ded;
	pthread_mutex_t		print_dead;
	pthread_mutex_t		*fork_tab;
	t_philo				**philo_tab;
	t_philo				*philo;
}				t_data;

//	main.c
int			main(int argc, char **argv);

//	ft_utils.c
int			ft_strlen(const char *str);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr(int nb);

//	ft_error.c
int			ft_isdigit(char *str);
int			ft_error(int argc, char **argv);

//	ft_atoi.c
int			ft_atoi(const char *nptr);

//	ft_init.c
void		ft_newphilo(t_data *data, int i);
void		ft_init_philo(t_data *data, int argc);
void		ft_init_fork(t_data *data);
void		ft_init_struct(t_data *data, int argc, char **argv);

//	ft_print.c
long long	ft_current_time(void);
char		*ft_display_string(int wich);
char		*ft_display_color(int wich);
void		ft_print_inf(t_philo *philo, int str);
void		ft_print_dead(t_philo *philo);

//	ft_routine.c
int			ft_check_status(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			ft_usleep(t_philo *philo, long long time);
int			ft_eat_last(t_philo *philo);
int			ft_eat(t_philo *philo);
void		*ft_routine(void *arg);

//	ft_clean.c
int			ft_join(t_data *data);
void		ft_clean_mutex(t_data *data);

#endif