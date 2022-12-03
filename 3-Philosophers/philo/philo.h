/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 19:00:20 by pdong         #+#    #+#                 */
/*   Updated: 2022/12/03 21:10:03 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>

typedef struct s_rules
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				c_eats;
	int				fullpeople;
	pthread_mutex_t	atetime;
	pthread_mutex_t	fulladd;
	pthread_mutex_t	printer;
	pthread_mutex_t	deadguy;
	long long		time;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				c_eats;
	int				dead;
	pthread_mutex_t	*fork;
	t_rules			*rules;
	long long		lastate;
}	t_philo;
void		*ft_calloc(int a, int count);
long long	ft_atoi(const char *str);
int			inputcheck(int ac, char **av);
long long	gettime(void);
void		ft_error(char *s, t_rules *rules, t_philo **philo, pthread_t *th);
void		logprint(t_philo *philo, char *s);
int			ft_idle(t_philo *philo, int time, char *s);
void		*action(void *p);
void		parsephilos(t_rules *rules, t_philo **philo);
void		threads_begin(t_rules *rules, t_philo **philo, pthread_t *th);
void		parserules(t_rules *rules, char **av);
int			fedpeople(t_philo *philo);
void		findforks(t_philo *a);
void		dropforks(t_philo *a);
void		philofree(t_philo **philo);
void		deadupdate(t_philo *a);
int			deadcheck(t_philo *philo);
int			fedcheck(t_rules *rules);
void		killall(t_rules *rules, t_philo **philo);

#endif