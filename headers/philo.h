/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:05:17 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/31 10:13:25 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"

# define RED "\033[31m"

# define GREEN "\033[32m"

# define YELLOW "\033[33m"

# define BLUE "\033[36m"

# define PINK "\033[35m"

typedef struct s_info_time
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned long	time_start;
	int				num_of_meal;
	pthread_mutex_t	writing;
}					t_info_time;

typedef struct s_philo
{
	t_info_time		*info;
	int				id;
	pthread_mutex_t	dead_mutex;
	int				dead;
	pthread_mutex_t	meal_mutex;
	unsigned long	last_meal;
	int				num_of_meal;
	pthread_mutex_t	finish_mutex;
	int				finish_diner;
	pthread_t		philosopher;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	int				first_action;
}					t_philo;

typedef struct s_monitor
{
	pthread_t		monitor;
	t_philo			*philo;
}					t_monitor;

// PARSING
void				check_info(t_info_time *info, char **argv, int argc);
void				init_struct(t_philo *philo, t_info_time *info);
void				set_the_table(t_monitor *monitor, t_info_time *info,
						t_philo *philo);

// UTILS PARSING
int					is_valid_args(int argc, char **argv);
void				ft_error(int flag_error);
bool				ft_atoi(const char *nptr, int *res);
void				ft_bzero(void *s, size_t n);

// UTILS
unsigned long		get_time_in_ms(void);
void				secure_print(char *s, t_philo *philo, char *color,
						unsigned long time_in_ms);
void				someone_died(t_philo *philo);

// ROUTINE
int					check_dead_flag(t_philo *philo);
void				*routine(void *philosopher);

// THINKING UTILS

void				even_philo_thinking(t_philo *philo,
						unsigned long thinking_time);
void				odd_philo_thinking(t_philo *philo,
						unsigned long thinking_time);

// MONITOR
void				*check_death(void *philosopher);

#endif