/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:22:43 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/31 13:48:32 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	even_philo_thinking(t_philo *philo, unsigned long thinking_time)
{
	unsigned long	time_in_ms;

	time_in_ms = get_time_in_ms();
	secure_print("is thinking", philo, GREEN, time_in_ms);
	if (philo->first_action)
	{
		philo->first_action = 0;
		usleep(philo->info->time_to_eat * 500);
	}
	else if (thinking_time)
		usleep(thinking_time);
	pthread_mutex_lock(philo->right_fork);
	time_in_ms = get_time_in_ms();
	secure_print("has taken a fork", philo, YELLOW, time_in_ms);
	pthread_mutex_lock(&philo->left_fork);
	time_in_ms = get_time_in_ms();
	secure_print("has taken a fork", philo, YELLOW, time_in_ms);
}

void	odd_philo_thinking(t_philo *philo, unsigned long thinking_time)
{
	unsigned long	time_in_ms;

	time_in_ms = get_time_in_ms();
	secure_print("is thinking", philo, GREEN, time_in_ms);
	usleep(5000 + thinking_time);
	time_in_ms = get_time_in_ms();
	pthread_mutex_lock(&philo->left_fork);
	time_in_ms = get_time_in_ms();
	secure_print("has taken a fork", philo, YELLOW, time_in_ms);
	pthread_mutex_lock(philo->right_fork);
	time_in_ms = get_time_in_ms();
	secure_print("has taken a fork", philo, YELLOW, time_in_ms);
}
