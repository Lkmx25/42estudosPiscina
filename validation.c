
#include "rushbsq.h"

int	first_line_validation(cf_map *config, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != config->empty && line[i] != config->obst)
			return (0);
		i++;
	}
	return (1);
}
