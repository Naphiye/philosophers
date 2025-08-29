/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:28:09 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/31 13:24:10 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	check_overflow_init_info(t_info_time *info, char **argv)
{
	if (!ft_atoi(argv[1], &info->number_of_philo) || !ft_atoi(argv[2],
			&info->time_to_die) || !ft_atoi(argv[3], &info->time_to_eat)
		|| !ft_atoi(argv[4], &info->time_to_sleep))
		ft_error(2);
	if (argv[5])
	{
		if (!ft_atoi(argv[5], &info->num_of_meal))
			ft_error(2);
	}
}

void	init_struct(t_philo *philo, t_info_time *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].info = info;
		philo[i].last_meal = info->time_start;
		philo[i].first_action = 1;
		philo[i].num_of_meal = philo->info->num_of_meal;
		philo[i].finish_diner = 0;
		if ((i + 1) == info->number_of_philo)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
		i++;
	}
}

void	check_info(t_info_time *info, char **argv, int argc)
{
	if (argc < 5 || argc > 6 || !is_valid_args(argc, argv))
		ft_error(1);
	ft_bzero(info, sizeof(t_info_time));
	check_overflow_init_info(info, argv);
}

void	set_the_table(t_monitor *monitor, t_info_time *info, t_philo *philo)
{
	int	i;

	i = 0;
	monitor->philo = philo;
	info->time_start = get_time_in_ms();
	while (i < info->number_of_philo)
	{
		pthread_mutex_init(&(philo[i].left_fork), NULL);
		pthread_mutex_init(&(philo[i].meal_mutex), NULL);
		pthread_mutex_init(&(philo[i].finish_mutex), NULL);
		pthread_mutex_init(&(philo[i++].dead_mutex), NULL);
	}
	init_struct(philo, info);
}
