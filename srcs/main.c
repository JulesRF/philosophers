/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:54:53 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/04/15 13:07:57 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ft_join(data);
	ft_clean_mutex(data);
	free(data);
	return (0);
}
