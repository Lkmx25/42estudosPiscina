/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:02:49 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 22:33:03 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

int	first_line_validation(t_map *config, char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] != config->empty && line[i] != config->obst)
			return (0);
		i++;
	}
	return (1);
}

void	set_dynamic_rows(char *line, t_map *configs, t_dyp *dynamic)
{
	int	i;

	i = 0;
	while (i < configs->cols)
	{
		if (line[i] == configs->empty)
			dynamic->prev_row[i] = 1;
		if (line[i] == configs->obst)
			dynamic->prev_row[i] = 0;
		i++;
	}
}

int	init_dynamic(int fd, t_map *config, t_dyp *dynamic)
{
	char	bfr[153600];
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n')
		bfr[i++] = c;
	bfr[i] = '\0';
	if (!first_line_validation(config, bfr))
		return (0);
	config->cols = ft_strlen(bfr);
	dynamic->curr_row = malloc(sizeof(int) * config->cols);
	dynamic->prev_row = malloc(sizeof(int) * config->cols);
	if (!dynamic->curr_row || !dynamic->prev_row)
	{
		free(dynamic->curr_row);
		free(dynamic->prev_row);
		return (0);
	}
	set_dynamic_rows(bfr, config, dynamic);
	return (1);
}

int	init_configs(int fd, t_map *configs)
{
	char	bfr[4096];
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n')
		bfr[i++] = c;
	bfr[i] = '\0';
	if (!has_valid_header(bfr))
		return (0);
	set_header_config(configs, bfr);
	return (1);
}

int	run_bsq_solver(char *path, t_map *configs, t_dyp *dynamic)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (!init_configs(fd, configs) || !init_dynamic(fd, configs, dynamic))
		return (0);
	if (configs->cols == 1 || configs->lines == 1)
		case_solver(fd, configs, dynamic);
	if (!solve_bsq(fd, configs, dynamic))
		return (0);
	close(fd);
	get_start_pos(dynamic);
	fd = open(path, O_RDONLY);
	write_bsq(fd, configs, dynamic);
	close(fd);
	return (1);
}
