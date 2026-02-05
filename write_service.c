/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_service.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:04:12 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 20:43:31 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

#define BUF_SIZE 8192

void	init_grid_state(int fd, t_dyp *dynamic, int *row, int *col)
{
	char	c;

	while (read(fd, &c, 1) > 0 && c != '\n')
		;
	*col = 0;
	*row = 0;
	dynamic->grid = malloc(sizeof(char *) * BUF_SIZE + 1);
}

int	has_bsq(t_dyp *dynamic, int row, int col)
{
	return (row >= dynamic->y_start && row <= dynamic->y_max
		&& col >= dynamic->x_start && col <= dynamic->x_max
		&& dynamic->v_max != 0);
}

void	next_row(int *row, int *col)
{
	*row = *row + 1;
	*col = 0;
}

void	set_bsq(t_dyp *dynamic, t_map *configs, int *i, int *col)
{
	dynamic->grid[*i] = configs->comp;
	*col = *col + 1;
}

int	write_bsq(int fd, t_map *configs, t_dyp *dynamic)
{
	int		i;
	char	buf[BUF_SIZE];
	int		bytes;
	int		row;
	int		col;

	init_grid_state(fd, dynamic, &row, &col);
	bytes = read(fd, buf, BUF_SIZE);
	while (bytes > 0)
	{
		i = -1;
		while (++i < bytes)
		{
			dynamic->grid[i] = buf[i];
			if (buf[i] == '\n')
				next_row(&row, &col);
			else if (has_bsq(dynamic, row, col))
				set_bsq(dynamic, configs, &i, &col);
			else
				col++;
		}
		write(1, dynamic->grid, i);
		bytes = read(fd, buf, BUF_SIZE);
	}
	return (free(dynamic->grid), 1);
}
