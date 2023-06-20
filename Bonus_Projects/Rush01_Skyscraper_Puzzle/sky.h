/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sky.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 10:54:16 by pdong         #+#    #+#                 */
/*   Updated: 2023/06/20 14:42:21 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKY_H
# define SKY_H
# include <stdlib.h>
# include <unistd.h>
# define SI 4

void	parse_input(char *s, int *ret);
int		input_check(char *s);
int		check_dup(int grid[SI][SI], int row, int col);
int		check_horizontal_left(int *input, int grid[SI][SI], int row);
int		check_horizontal_right(int *input, int grid[SI][SI], int row);
int		check_vertical_top(int *input, int grid[SI][SI], int col);
int		check_vertical_bottom(int *input, int grid[SI][SI], int col);
int		is_valid(int *input, int grid[SI][SI], int row, int col);
int		solve(int *input, int grid[SI][SI], int row, int col);
void	print_answer(int ans[SI][SI]);
void	initialize(int ans[SI][SI]);

#endif
