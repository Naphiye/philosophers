/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:36 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/21 15:49:47 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	create_all_philo_thread(t_info_time *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_create(&(philo[i].philosopher), NULL, &routine,
			(void *)&philo[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_philo		*philo;
	t_monitor	monitor;
	t_info_time	info;

	i = 0;
	check_info(&info, argv, argc);
	philo = malloc(sizeof(t_philo) * info.number_of_philo);
	if (!philo)
		ft_error(4);
	set_the_table(&monitor, &info, philo);
	create_all_philo_thread(&info, philo);
	pthread_create(&(monitor.monitor), NULL, &check_death, (void *)philo);
	while (i < info.number_of_philo)
	{
		pthread_join(philo[i].philosopher, NULL);
		i++;
	}
	pthread_join(monitor.monitor, NULL);
	free(philo);
	return (0);
}
