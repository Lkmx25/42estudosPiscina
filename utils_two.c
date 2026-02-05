/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:02:37 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 21:44:12 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

static int	process_map(char *path, t_map *configs, t_dyp *dynamic)
{
	set_struct(configs, dynamic);
	if (!run_bsq_solver(path, configs, dynamic))
		return (0);
	return (1);
}

char	*read_stdin(void)
{
	int		fd_file;
	char	*bfr;
	int		bytes;

	bfr = malloc(153600);
	if (!bfr)
		exit(1);
	fd_file = open("map.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_file < 0)
	{
		free(bfr);
		exit(1);
	}
	bytes = read(0, bfr, 8192);
	while (bytes > 0)
	{
		write(fd_file, bfr, bytes);
		bytes = read(0, bfr, 8192);
	}
	close(fd_file);
	free(bfr);
	return ("map.txt");
}

void	set_args(int ac, char **av, t_map *configs, t_dyp *dynamic)
{
	int		i;
	char	*path;

	i = 1;
	if (ac == 1)
	{
		path = read_stdin();
		if (!process_map(path, configs, dynamic))
			write(1, "map error\n", 10);
	}
	else
	{
		while (i < ac)
		{
			if (!process_map(av[i++], configs, dynamic))
			{
				if (i < ac)
					write(1, "map error\n", 10);
				else
					write(1, "map error", 10);
			}
			if (i < ac)
				write(1, "\n", 1);
		}
	}
}

int	ft_min(int a, int b, int c)
{
	int	min;

	min = a;
	if (b < a)
		min = b;
	if (c < b)
		min = c;
	return (min);
}

void	get_start_pos(t_dyp *dynamic)
{
	if (dynamic->y_max == 0)
		dynamic->y_start = dynamic->y_max;
	else
		dynamic->y_start = dynamic->y_max - dynamic->v_max + 1;
	if (dynamic->x_max == 0)
	{
		dynamic->x_start = dynamic->x_max;
		dynamic->y_start = dynamic->y_max;
	}
	else
		dynamic->x_start = dynamic->x_max - dynamic->v_max + 1;
}
