/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 20:26:35 by pdong         #+#    #+#                 */
/*   Updated: 2022/12/03 21:33:22 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	findforks(t_philo *a)
{
	if (a)
		pthread_mutex_lock(&a->fork[0]);
	logprint(a, "has taken a fork");
	if (a && a->id == a->rules->n_philo)
		pthread_mutex_lock(&a->fork[a->id * -1 + 1]);
	else if (a)
		pthread_mutex_lock(&a->fork[1]);
	logprint(a, "has taken a fork");
}

void	dropforks(t_philo *a)
{
	if (a && a->id == a->rules->n_philo)
		pthread_mutex_unlock(&a->fork[a->id * -1 + 1]);
	else if (a)
		pthread_mutex_unlock(&a->fork[1]);
	if (a)
		pthread_mutex_unlock(&a->fork[0]);
	if (a)
	{
		pthread_mutex_lock(&a->rules->atetime);
		a->lastate = gettime();
		pthread_mutex_unlock(&a->rules->atetime);
	}
	if (a)
		a->c_eats++;
}

int	fedpeople(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fulladd);
	if (philo->c_eats == philo->rules->c_eats)
		philo->rules->fullpeople++;
	if (philo->rules->fullpeople >= philo->rules->n_philo)
	{
		pthread_mutex_unlock(&philo->rules->fulladd);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->fulladd);
		return (0);
	}
}

void	philofree(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->rules->n_philo)
		pthread_mutex_destroy(philo[i++]->fork);
	if (philo[0]->fork)
		free(philo[0]->fork);
	i = 0;
	while (philo && philo[i])
	{
		pthread_mutex_destroy(philo[i]->fork);
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	deadupdate(t_philo *a)
{
	pthread_mutex_lock(&a->rules->deadguy);
	a->dead = 1;
	pthread_mutex_unlock(&a->rules->deadguy);
}
