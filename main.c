/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:04:35 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 20:08:52 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

static int	alloc_struct(t_map **configs, t_dyp **dynamic)
{
	*configs = malloc(sizeof(t_map));
	if (!*configs)
		return (0);
	*dynamic = malloc(sizeof(t_dyp));
	if (!*dynamic)
	{
		free(*configs);
		return (0);
	}
	return (1);
}

static int	free_struct(t_map **configs, t_dyp **dynamic)
{
	if (*dynamic)
	{
		free((*dynamic)->curr_row);
		free((*dynamic)->prev_row);
		free(*dynamic);
	}
	if (*configs)
		free(*configs);
	return (1);
}

void	set_struct(t_map *configs, t_dyp *dynamic)
{
	configs->lines = 0;
	configs->cols = 0;
	configs->comp = '\0';
	configs->empty = '\0';
	configs->obst = '\0';
	dynamic->v_max = 0;
	dynamic->x_max = 0;
	dynamic->y_max = 0;
	dynamic->x_start = 0;
	dynamic->y_start = 0;
	dynamic->curr_row = NULL;
	dynamic->prev_row = NULL;
	dynamic->grid = NULL;
}

int	main(int ac, char **av)
{
	t_dyp	*dynamic;
	t_map	*configs;

	dynamic = NULL;
	configs = NULL;
	if (!alloc_struct(&configs, &dynamic))
		return (0);
	set_args(ac, av, configs, dynamic);
	free_struct(&configs, &dynamic);
	return (0);
}
