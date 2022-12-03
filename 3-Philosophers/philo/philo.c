/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 20:45:01 by pdong         #+#    #+#                 */
/*   Updated: 2022/12/03 21:29:02 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logprint(t_philo *philo, char *s)
{
	if (!philo)
		return ;
	pthread_mutex_lock(&philo->rules->printer);
	printf("%lld %d %s\n", gettime() - philo->rules->time, philo->id, s);
	pthread_mutex_unlock(&philo->rules->printer);
}

int	ft_idle(t_philo *philo, int time, char *s)
{
	long long	temp;

	if (!philo)
		return (0);
	temp = gettime();
	logprint(philo, s);
	while (gettime() - temp < time)
	{
		usleep(250);
		pthread_mutex_lock(&philo->rules->atetime);
		if (gettime() - philo->lastate > philo->rules->t_die)
		{
			pthread_mutex_unlock(&philo->rules->atetime);
			deadupdate(philo);
			return (0);
		}
		pthread_mutex_unlock(&philo->rules->atetime);
	}
	return (1);
}

void	parsephilos(t_rules *rules, t_philo **philo)
{
	int				i;
	pthread_mutex_t	printer;
	pthread_mutex_t	*fork;

	i = 0;
	pthread_mutex_init(&printer, NULL);
	fork = ft_calloc(rules->n_philo + 1, sizeof(pthread_mutex_t));
	if (!fork)
		ft_error("rfork calloc failed.", rules, philo, 0);
	while (i < rules->n_philo)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			ft_error("philo[i] calloc failed.", rules, philo, 0);
		pthread_mutex_init(&fork[i], NULL);
		philo[i]->id = i + 1;
		philo[i]->rules = rules;
		philo[i]->fork = &fork[i];
		philo[i]->lastate = rules->time;
		i++;
	}
}

void	*action(void *p)
{
	t_philo	*a;

	a = (t_philo *)(p);
	if (a->id % 2 == 0)
		usleep(5000);
	while (a && deadcheck(a))
	{
		findforks(a);
		if (!a || !ft_idle(a, a->rules->t_eat, "is eating") || !deadcheck(a))
		{
			dropforks(a);
			break ;
		}
		dropforks(a);
		if (!a || fedpeople(a) || !ft_idle(a, a->rules->t_sleep, "is sleeping")
			|| !deadcheck(a))
			break ;
		logprint(a, "is thinking");
	}
	return (0);
}

void	threads_begin(t_rules *rules, t_philo **philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_create(&th[i], NULL, action, philo[i]))
			return (ft_error("Thread create failed.", rules, philo, th));
		i++;
	}
	i = 0;
	while (1)
	{
		if (!deadcheck(philo[i]))
			break ;
		if (!fedcheck(rules))
			return (ft_error("Simulation Complete!", rules, philo, th));
		i++;
		if (i == rules->n_philo)
			i = 0;
	}
	killall(rules, philo);
	logprint(philo[i], "died");
	ft_error("Simulation Complete!", rules, philo, th);
}
