
#ifndef RUSHBSQ

# define RUSHBSQ

# include "utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int		lines;
	int		cols;
	char	empty;
	char	obst;
	char	comp;
}			cf_map;

typedef struct s_dyp
{
	int		v_max;
	int		x_max;
	int		y_max;
	int		*curr_row;
	int		*prev_row;
	char	**grid;
}			t_dyp;

/* Headers validate and parsing*/
int			ft_atoi_header(char *str);
void		ft_parse_header(cf_map *map, char *line);
int			validate_header(char *line);

/* Memory allocation and free*/
int			first_line_dp(char *line, cf_map *config, t_dyp *dynamic);
int			first_line_validation(cf_map *config, char *line);

/* Solver*/
void		translate_map(char *line, cf_map *configs, t_dyp *dynamic);
int			first_reader(int fd, cf_map *configs, t_dyp *dynamic);
int			read_line_per_line(int fd, cf_map *configs, t_dyp *dynamic);
void		solver_dp(cf_map *configs, t_dyp *dynamic, int lines);
int			read_and_memory(char *path, cf_map *configs, t_dyp *dynamic);

#endif