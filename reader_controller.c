
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

int	first_reader(int fd, cf_map *configs, t_dyp *dynamic)
{
	char	bfr[4096];
	char	c;
	int		i;
	int		is_first;

	is_first = 0;
	i = 0;
	
	while (read(fd, &c, 1) > 0)
	{
		printf("%c", c);
		
		if (c != '\n' && i < 4095)
			bfr[i++] = c;
		if (c == '\n' && is_first == 0)
		{
			bfr[i] = '\0';
			if (!validate_header(bfr))
				return (0);
			ft_parse_header(configs, bfr);
			is_first = 1;
			i = 0;
			continue;
		}
		if (c == '\n' && is_first == 1)
		{
			bfr[i] = '\0';
			if (!first_line_dp(bfr, configs, dynamic))
				return (0);
			break ;
		}
	}
	return (1);
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
	while (i < configs->lines - 1)
	{
		bytes_read = read(fd, bfr, configs->cols + 1);
		if ((bytes_read - 1) != configs->cols && bfr[configs->cols] != '\n')
		{
			free(bfr);
			return (0);
		}
		bfr[configs->cols] = '\0';
		translate_map(bfr, configs, dynamic);
		solver_dp(configs, dynamic, i);
		swap_pointer(&dynamic->curr_row, &dynamic->prev_row);
		i++;
	}
	free(bfr);
	return (1);
}

void	translate_map(char *line, cf_map *configs, t_dyp *dynamic)
{
	int	i;

	i = 0;
	while (i < configs->cols)
	{
		if (line[i] == configs->empty)
			dynamic->curr_row[i] = 1;
		if (line[i] == configs->obst)
			dynamic->curr_row[i] = 0;
		i++;
	}
}

void	solver_dp(cf_map *configs, t_dyp *dynamic, int lines)
{
	int	diagonal;
	int	left;
	int	top;
	int	i;

	i = 1;
	while (i < configs->cols)
	{
		diagonal = dynamic->prev_row[i - 1];
		left = dynamic->curr_row[i - 1];
		top = dynamic->prev_row[i];
		if (dynamic->curr_row[i] != 0)
		{
			dynamic->curr_row[i] = 1 + ft_min(diagonal, left, top);
		}
		if (dynamic->curr_row[i] > dynamic->v_max)
		{
			dynamic->v_max = dynamic->curr_row[i];
			dynamic->x_max = i;
			dynamic->y_max = lines;
		}
		i++;
	}
}
