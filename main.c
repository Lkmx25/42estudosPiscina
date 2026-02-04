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
	else if (mode == 0)
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
	dynamic->curr_row = NULL;
	dynamic->prev_row = NULL;
}

static void	process_map(char *path, cf_map *configs, t_dyp *dynamic)
{
	set_struct(configs, dynamic);
	if (read_and_memory(path, configs, dynamic))
	{

		// print_res(path, configs, dynamic);
	}
	else
		write(2, "map error\n", 10);
	if (dynamic->curr_row)
		free(dynamic->curr_row);
	if (dynamic->prev_row)
		free(dynamic->prev_row);
	dynamic->curr_row = NULL;
	dynamic->prev_row = NULL;
}

static void	set_args(int ac, char **av, cf_map *configs, t_dyp *dynamic)
{
	int	i;

	if (ac == 1)
	{
		// handle_stdin(".temp"); 
		// process_map(".temp", configs, dynamic);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			process_map(av[i], configs, dynamic);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_dyp	*dynamic;
	cf_map	*configs;

	dynamic = NULL;
	configs = NULL;
	if (!alloc_struct(&configs, &dynamic, 1))
		return (0);
	set_args(ac, av, configs, dynamic);
	alloc_struct(&configs, &dynamic, 0);
	return (0);
}
