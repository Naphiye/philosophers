/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:18:30 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/21 15:49:31 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

unsigned long	get_time_in_ms(void)
{
	struct timeval	time;
	unsigned long	time_stamp;

	gettimeofday(&time, NULL);
	time_stamp = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	return (time_stamp);
}

void	secure_print(char *s, t_philo *philo, char *color,
		unsigned long time_in_ms)
{
	unsigned long	time;

	time = time_in_ms - philo->info->time_start;
	if (check_dead_flag(philo))
		return ;
	pthread_mutex_lock(&philo->info->writing);
	printf("%s%ld %d %s%s\n", color, time, philo->id, s, RESET);
	pthread_mutex_unlock(&philo->info->writing);
}

void	someone_died(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->number_of_philo)
	{
		pthread_mutex_lock(&philo[i].dead_mutex);
		philo[i].dead = 1;
		pthread_mutex_unlock(&philo[i].dead_mutex);
		i++;
	}
}
