/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:05:21 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 04:00:01 by kali          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct the_lst
{
	struct the_lst	*prev;
	int				content;
	struct the_lst	*next;
}	t_lst;

t_lst	*ft_lnew(int content);
void	ft_ladd_end(t_lst **lst, t_lst *new);
void	ft_ladd_start(t_lst **lst, t_lst *new);
int		lstsize(t_lst **a);
void	ft_error(void);
void	parser(t_lst **a, char **s, int ac);
void	parser2(t_lst **a, char **s, int ac);
void	supersolver(t_lst **a, t_lst **b);
void	solvera(t_lst **a, t_lst **b, int buf);
void	solverb(t_lst **b, t_lst **a, int buf);
void	inputcheck(char **s, int ac);
int		checkera(t_lst **a);
int		checkerb(t_lst **b);
void	ft_swap(t_lst **a);
void	ft_push(t_lst **a, t_lst **b);
void	ft_rotate(t_lst **a);
void	ft_rrotate(t_lst **a);
int		num_sorted(t_lst **a, t_lst **b);
int		num_sorted2(t_lst **b, int content, int i);
int		ft_mediana(t_lst **a, int buf);
int		ft_medianb(t_lst **b, int buf);
void	lstsplit(t_lst **a, t_lst **b, int median, int buf);
void	lstsplit2(t_lst **a, int j, int buf);
void	rlstsplit(t_lst **a, t_lst **b, int median, int buf);
void	rlstsplit2(t_lst **b, int j);
void	twosort(t_lst **a, t_lst **b);
void	twosortab(t_lst **a, t_lst **b);
void	threesort(t_lst **a, t_lst **b);
void	checkthirda(t_lst **a, t_lst **b);
void	checkthirdb(t_lst **a, t_lst **b);
void	checkthirdab(t_lst **a, t_lst **b);
void	pushnsortb(t_lst **a, t_lst **b);
int		getindexb(t_lst **b, int j);
void	fivesort(t_lst **a, t_lst **b);
void	fiverotate(t_lst **a, int size);
int		minindex(t_lst **a);
void	freesplit(char **arr);
void	singlecase(char **arr);
void	ft_dupcheck(t_lst **a);
void	arroverflow(char **arr);

#endif