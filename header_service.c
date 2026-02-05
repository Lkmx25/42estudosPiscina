/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:02:43 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 20:08:52 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

int	atoi_header(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res < 0)
		return (0);
	return (res);
}

int	has_valid_header(char *line)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(line);
	if (len < 4)
		return (0);
	while (i < 4)
	{
		if (!ft_is_printable(line[len - i]))
			return (0);
		i++;
	}
	if (!compare_char(line[len - 1], line[len - 2], line[len - 3]))
		return (0);
	i = 0;
	while (i < len - 3)
	{
		if (!ft_is_digit(line[i]))
			return (0);
		i++;
	}
	if (atoi_header(line) == 0)
		return (0);
	return (1);
}

void	set_header_config(t_map *map, char *line)
{
	char	line_temp[512];
	int		i;
	int		length;

	i = 0;
	length = ft_strlen(line);
	map->comp = line[length - 1];
	map->obst = line[length - 2];
	map->empty = line[length - 3];
	while (i < length - 3)
	{
		line_temp[i] = line[i];
		i++;
	}
	line_temp[i] = '\0';
	map->lines = atoi_header(line_temp);
}

void	case_solver(int fd, t_map *configs, t_dyp *dynamics)
{
	if (dynamics->prev_row[0] == 1)
	{
		dynamics->v_max = dynamics->prev_row[0];
		dynamics->x_max = 0;
		dynamics->y_max = 0;
	}
	else if (configs->lines == 1)
		solve_one_line(dynamics, configs);
	else
		solve_one_col(fd, configs, dynamics, 0);
}
