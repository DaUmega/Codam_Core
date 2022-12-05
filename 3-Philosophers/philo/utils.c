/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 19:00:26 by pdong         #+#    #+#                 */
/*   Updated: 2022/12/05 18:19:18 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(int a, int count)
{
	char	*s;

	s = malloc(a * count);
	if (!s)
		return (NULL);
	s = memset(s, 0, a * count);
	return (s);
}

long long	ft_atoi(const char *str)
{
	int			i;
	long long	ans;

	i = 0;
	ans = 0;
	while (str[i] >= '0' && str[i] <= '9')
		ans = 10 * ans + (str[i++] - '0');
	return (ans);
}

int	inputcheck(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == 0 || av[i][0] == '0')
			return (0);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		if (ft_atoi(av[i]) > INT_MAX || ft_atoi(av[2]) == 0)
			return (0);
		i++;
	}
	return (1);
}

long long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_error(char *s, t_rules *rules, t_philo **philo, pthread_t *th)
{
	int	i;

	i = 0;
	if (rules)
		pthread_mutex_lock(&rules->printer);
	usleep(1000000);
	if (th)
	{
		while (i < rules->n_philo)
			if (pthread_detach(th[i++]))
				break ;
		free(th);
	}
	i = 0;
	if (philo)
		philofree(philo);
	if (rules)
		free(rules);
	printf("%s\n", s);
}
