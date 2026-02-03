
#include "rushbsq.h"

static int	alloc_struct(cf_map **configs, t_dyp **dynamic, int mode)
{
	if (mode == 1)
	{
		*configs = malloc(sizeof(cf_map));
		if (!*configs)
			return (0);
		*dynamic = malloc(sizeof(t_dyp));
		if (!*dynamic)
		{
			free(*configs);
			return (0);
		}
	}
	if (mode == 0)
	{
		if (*dynamic)
		{
			free((*dynamic)->curr_row);
			free((*dynamic)->prev_row);
			free(*dynamic);
		}
		if (*configs)
			free(*configs);
	}
	return (1);
}

static void	set_struct(cf_map *configs, t_dyp *dynamic)
{
	configs->lines = 0;
	configs->cols = 0;
	configs->comp = '\0';
	configs->empty = '\0';
	configs->obst = '\0';
	dynamic->v_max = 0;
	dynamic->x_max = 0;
	dynamic->y_max = 0;
	// dynamic->curr_row;
	// dynamic->prev_row;
}

int	main(int ac, char **av)
{
	t_dyp	*dynamic;
	cf_map	*configs;
	char	*path;

	if (!alloc_struct(&configs, &dynamic, 1))
		return (0);
	set_struct(configs, dynamic);
	if (ac > 1)
	{
		path = av[1];
		read_and_memory(path, configs, dynamic);
        printf("valor do x:%d, valor do y:%d e valor total:%d", dynamic->x_max, dynamic->y_max, dynamic->v_max);
	}
	alloc_struct(&configs, &dynamic, 0);
}
