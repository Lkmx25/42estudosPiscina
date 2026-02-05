/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_service.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:03:02 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 21:36:52 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

int	translate_map(char *line, t_map *configs, t_dyp *dynamic)
{
	int	i;

	i = 0;
	while (i < configs->cols)
	{
		if (line[i] != configs->empty && line[i] != configs->obst)
			return (0);
		if (line[i] == configs->empty)
			dynamic->curr_row[i] = 1;
		if (line[i] == configs->obst)
			dynamic->curr_row[i] = 0;
		i++;
	}
	return (1);
}

void	solver_dp(t_map *configs, t_dyp *dynamic, int lines)
{
	int	topleft;
	int	left;
	int	top;
	int	i;

	i = 1;
	while (i < configs->cols)
	{
		topleft = dynamic->prev_row[i - 1];
		left = dynamic->curr_row[i - 1];
		top = dynamic->prev_row[i];
		if (dynamic->curr_row[i] != 0)
			dynamic->curr_row[i] = 1 + ft_min(topleft, left, top);
		if (dynamic->curr_row[i] > dynamic->v_max)
		{
			dynamic->v_max = dynamic->curr_row[i];
			dynamic->x_max = i;
			dynamic->y_max = lines;
		}
		i++;
	}
}

int	solve_bsq(int fd, t_map *configs, t_dyp *dynamic)
{
	int		i;
	int		bytes_read;
	char	*bfr;

	bfr = malloc(sizeof(char) * (configs->cols + 1));
	if (!bfr)
		return (0);
	i = 1;
	while (i < configs->lines + 1)
	{
		bytes_read = read(fd, bfr, configs->cols + 1);
		if (bytes_read <= 0)
			break ;
		if (bfr[configs->cols] == '\n')
			bfr[configs->cols] = '\0';
		if (!translate_map(bfr, configs, dynamic))
			return (0);
		solver_dp(configs, dynamic, i);
		swap_pointer(&dynamic->curr_row, &dynamic->prev_row);
		i++;
	}
	if (i > configs->lines)
		return (0);
	return (free(bfr), 1);
}

void	solve_one_line(t_dyp *dyn, t_map *configs)
{
	int	i;
	int	first_spot;

	i = 0;
	first_spot = 0;
	while (i < configs->cols)
	{
		if (first_spot == 0 && dyn->prev_row[i] == 1)
		{
			dyn->v_max = dyn->prev_row[i];
			dyn->x_max = i;
			dyn->y_max = 0;
			first_spot = 1;
		}
		i++;
	}
}

void	solve_one_col(int fd, t_map *configs, t_dyp *dyn, int first_spot)
{
	int		i;
	int		bytes_read;
	char	*bfr;

	bfr = malloc(sizeof(char) * (configs->cols + 1));
	if (!bfr)
		return ;
	i = 1;
	while (i < configs->lines)
	{
		bytes_read = read(fd, bfr, configs->cols + 1);
		if (bytes_read <= 0)
			break ;
		bfr[configs->cols] = '\0';
		translate_map(bfr, configs, dyn);
		if (dyn->curr_row[0] == 1 && first_spot == 0)
		{
			dyn->v_max = 1;
			dyn->x_max = 0;
			dyn->y_max = i;
			first_spot = 1;
		}
		i++;
	}
}
