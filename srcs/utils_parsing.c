/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalomon <fsalomon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:54:18 by fsalomon          #+#    #+#             */
/*   Updated: 2024/05/31 13:24:24 by fsalomon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	is_positiv_number(char *arg, int arg_num)
{
	int	i;

	i = 0;
	if (arg && arg[0] == '+')
		i++;
	else if (arg && arg[0] == '0' && arg[1] == 0 && arg_num != 5)
		return (0);
	while (arg && arg[i])
	{
		if (arg[i] < 48 || arg[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_positiv_number(argv[i], i))
			return (0);
		i++;
	}
	return (1);
}

void	ft_error(int flag_error)
{
	if (flag_error == 1)
		write(2, "Program needs 4 or 5 arguments in strictly positiv number\n",
			59);
	else if (flag_error == 2)
		write(2, "Int overflow\n", 14);
	else if (flag_error == 4)
		write(2, "Malloc error \n", 15);
	exit(0);
}

bool	ft_atoi(const char *nptr, int *res)
{
	int	i;

	i = 0;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] != 0 && nptr[i] > 47 && nptr[i] < 58)
	{
		if (*res > (INT_MAX / 10) || (*res == (INT_MAX / 10) && (nptr[i]
					- '0') > INT_MAX % 10))
			return (false);
		*res = *res * 10 + (nptr[i] - '0');
		i++;
	}
	return (true);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	c;

	c = 0;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
}
