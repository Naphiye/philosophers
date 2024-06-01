/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:40:53 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/21 16:11:51 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

unsigned long	get_last_meal_time(t_philo *philo)
{
	unsigned long	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_meal);
}

int	get_finish_diner(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->finish_mutex);
	res = philo->finish_diner;
	pthread_mutex_unlock(&philo->finish_mutex);
	return (res);
}

int	they_finish_dining(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->number_of_philo)
	{
		pthread_mutex_lock(&philo[i].finish_mutex);
		if (!philo[i].finish_diner)
		{
			pthread_mutex_unlock(&philo[i].finish_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].finish_mutex);
		i++;
	}
	return (1);
}

void	*check_death(void *philosopher)
{
	t_philo			*philo;
	int				i;
	unsigned long	time;
	unsigned long	last_meal;

	philo = (t_philo *)philosopher;
	while (1)
	{
		i = 0;
		while (i < philo->info->number_of_philo)
		{
			time = get_time_in_ms();
			last_meal = get_last_meal_time(&philo[i]);
			if ((int)(time - last_meal) >= philo[i].info->time_to_die
				&& !(get_finish_diner(&philo[i])))
			{
				secure_print("died", &philo[i], RED, time);
				return (someone_died(philo), NULL);
			}
			i++;
		}
		if (they_finish_dining(philo))
			return (NULL);
	}
	return (NULL);
}
