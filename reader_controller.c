
#include "rushbsq.h"

int	read_and_memory(char *path, cf_map *configs, t_dyp *dynamic)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (!first_reader(fd, configs, dynamic))
		return (0);
	if (!read_line_per_line(fd, configs, dynamic))
		return (0);
	close(fd);
	return (1);
}

static int	process_first_line(int fd, cf_map *cfg, t_dyp *dyp)
{
	char	bfr[4096];
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n' && i < 4095)
		bfr[i++] = c;
	bfr[i] = '\0';
	if (!first_line_dp(bfr, cfg, dyp))
		return (0);
	return (1);
}

int	first_reader(int fd, cf_map *configs, t_dyp *dynamic)
{
	char	bfr[4096];
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n' && i < 4095)
		bfr[i++] = c;
	bfr[i] = '\0';
	if (!validate_header(bfr))
		return (0);
	ft_parse_header(configs, bfr);
	return (process_first_line(fd, configs, dynamic));
}

int	read_line_per_line(int fd, cf_map *configs, t_dyp *dynamic)
{
	int		i;
	int		bytes_read;
	char	*bfr;

	bfr = malloc(sizeof(char) * (configs->cols + 1));
	if (!bfr)
		return (0);
	i = 1;
	while (i < configs->lines)
	{
		bytes_read = read(fd, bfr, configs->cols + 1);
		if (bytes_read <= 0)
			break ;
		bfr[configs->cols] = '\0';
		translate_map(bfr, configs, dynamic, i);
		solver_dp(configs, dynamic, i);
		swap_pointer(&dynamic->curr_row, &dynamic->prev_row);
		i++;
	}
	free(bfr);
	return (1);
}

void	translate_map(char *line, cf_map *configs, t_dyp *dynamic, int y)
{
	int	i;

	i = 0;
	while (i < configs->cols)
	{
		if (line[i] == configs->empty)
			dynamic->curr_row[i] = 1;
		else if (line[i] == configs->obst)
			dynamic->curr_row[i] = 0;
		if (dynamic->curr_row[i] > dynamic->v_max)
		{
			dynamic->v_max = dynamic->curr_row[i];
			dynamic->x_max = i;
			dynamic->y_max = y;
		}
		i++;
	}
}

void	solver_dp(cf_map *configs, t_dyp *dynamic, int y)
{
	int	i;
	int	min;

	i = 1;
	while (i < configs->cols)
	{
		if (dynamic->curr_row[i] != 0)
		{
			min = ft_min(dynamic->prev_row[i - 1],
					dynamic->curr_row[i - 1], dynamic->prev_row[i]);
			dynamic->curr_row[i] = 1 + min;
		}
		if (dynamic->curr_row[i] > dynamic->v_max)
		{
			dynamic->v_max = dynamic->curr_row[i];
			dynamic->x_max = i;
			dynamic->y_max = y;
		}
		i++;
	}
}
