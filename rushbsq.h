/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushbsq.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:04:59 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 21:18:55 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSHBSQ_H

# define RUSHBSQ_H

# include "utils.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int		lines;
	int		cols;
	char	empty;
	char	obst;
	char	comp;
}			t_map;

typedef struct s_dyp
{
	int		v_max;
	int		x_max;
	int		y_max;
	int		x_start;
	int		y_start;
	int		*curr_row;
	int		*prev_row;
	char	*grid;
}			t_dyp;

/* Headers validate and parsing*/
void		set_header_config(t_map *map, char *line);
int			has_valid_header(char *line);

/* Memory allocation and free*/
int			first_line_validation(t_map *config, char *line);

/* Solver*/
int			translate_map(char *line, t_map *configs, t_dyp *dynamic);
void		solver_dp(t_map *configs, t_dyp *dynamic, int lines);
int			run_bsq_solver(char *path, t_map *configs, t_dyp *dynamic);
int			solve_bsq(int fd, t_map *configs, t_dyp *dynamic);
int			write_bsq(int fd, t_map *configs, t_dyp *dynamic);
void		get_start_pos(t_dyp *dynamic);
void		set_args(int ac, char **av, t_map *configs, t_dyp *dynamic);
void		set_struct(t_map *configs, t_dyp *dynamic);
void		get_start_pos(t_dyp *dynamic);
void		solve_one_line(t_dyp *dyn, t_map *configs);
void		solve_one_col(int fd, t_map *configs, t_dyp *dyn, int first_spot);
void		case_solver(int fd, t_map *configs, t_dyp *dynamics);

#endif