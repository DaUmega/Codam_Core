/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 19:00:09 by pdong         #+#    #+#                 */
/*   Updated: 2022/12/03 21:09:56 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	killall(t_rules *rules, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
		deadupdate(philo[i++]);
}

int	deadcheck(t_philo *a)
{
	pthread_mutex_lock(&a->rules->deadguy);
	if (a->dead == 1)
	{
		pthread_mutex_unlock(&a->rules->deadguy);
		return (0);
	}
	pthread_mutex_unlock(&a->rules->deadguy);
	pthread_mutex_lock(&a->rules->atetime);
	if (gettime() - a->lastate >= a->rules->t_die)
		deadupdate(a);
	pthread_mutex_unlock(&a->rules->atetime);
	return (1);
}

int	fedcheck(t_rules *rules)
{
	pthread_mutex_lock(&rules->fulladd);
	if (rules->c_eats != 0 && rules->n_philo <= rules->fullpeople)
	{
		pthread_mutex_unlock(&rules->fulladd);
		return (0);
	}
	pthread_mutex_unlock(&rules->fulladd);
	return (1);
}

void	parserules(t_rules *rules, char **av)
{
	pthread_mutex_t	fulladd;
	pthread_mutex_t	printer;
	pthread_mutex_t	ate;
	pthread_mutex_t	dead;

	if (pthread_mutex_init(&fulladd, NULL) || pthread_mutex_init(&printer, NULL)
		|| pthread_mutex_init(&ate, NULL) || pthread_mutex_init(&dead, NULL))
		return (ft_error("mutex init failed", rules, 0, 0));
	rules->n_philo = ft_atoi(av[1]);
	if (rules->n_philo < 1)
		return (ft_error("Number of philosophers must be > 1.", rules, 0, 0));
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		rules->c_eats = ft_atoi(av[5]);
		if (rules->c_eats == 0)
			return (ft_error("Simulation Complete!", rules, 0, 0));
	}
	rules->time = gettime();
	rules->fulladd = fulladd;
	rules->printer = printer;
	rules->atetime = ate;
	rules->deadguy = dead;
}

int	main(int ac, char **av)
{
	t_rules		*rules;
	t_philo		**philo;
	pthread_t	*th;

	if (ac != 5 && ac != 6)
		return (ft_error("Incorrect number of arguments.", 0, 0, 0), 0);
	if (!inputcheck(ac, av))
		return (ft_error("Incorrect inputs, + ints only.", 0, 0, 0), 0);
	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (ft_error("Rules calloc failed.", 0, 0, 0), 0);
	parserules(rules, av);
	philo = ft_calloc(rules->n_philo + 1, sizeof(t_philo *));
	if (!philo)
		return (ft_error("Philo calloc failed.", rules, 0, 0), 0);
	parsephilos(rules, philo);
	th = ft_calloc(rules->n_philo + 1, sizeof(pthread_t));
	if (!th)
		return (ft_error("Threads calloc failed.", rules, 0, 0), 0);
	threads_begin(rules, philo, th);
	return (0);
}
