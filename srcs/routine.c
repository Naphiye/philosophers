/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:38:51 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/31 13:44:25 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	check_dead_flag(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->dead_mutex);
	dead = philo->dead;
	pthread_mutex_unlock(&philo->dead_mutex);
	return (dead);
}

void	sleeping(t_philo *philo)
{
	unsigned long	time_in_ms;

	time_in_ms = get_time_in_ms();
	secure_print("is sleeping", philo, BLUE, time_in_ms);
	usleep(philo->info->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	unsigned long	think_time;

	if (philo->info->number_of_philo % 2 != 0
		&& philo->info->time_to_eat > philo->info->time_to_sleep)
		think_time = (philo->info->time_to_eat - philo->info->time_to_sleep)
			* 1000;
	else
		think_time = 0;
	if (philo->id % 2 == 0)
		even_philo_thinking(philo, think_time);
	else
		odd_philo_thinking(philo, think_time);
}

void	eating(t_philo *philo)
{
	unsigned long	time_in_ms;

	time_in_ms = get_time_in_ms();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time_in_ms;
	pthread_mutex_unlock(&philo->meal_mutex);
	time_in_ms = get_time_in_ms();
	secure_print("is eating", philo, PINK, time_in_ms);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->info->number_of_philo == 1)
	{
		secure_print("has taken a fork", philo, YELLOW, get_time_in_ms());
		usleep(philo->info->time_to_die * 1000);
		secure_print("died", philo, RED, get_time_in_ms());
		return (NULL);
	}
	while (!check_dead_flag(philo))
	{
		thinking(philo);
		eating(philo);
		philo->num_of_meal--;
		if (philo->num_of_meal == 0)
		{
			pthread_mutex_lock(&philo->finish_mutex);
			philo->finish_diner = 1;
			pthread_mutex_unlock(&philo->finish_mutex);
			return (NULL);
		}
		sleeping(philo);
	}
	return (NULL);
}
