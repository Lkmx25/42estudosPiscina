#include "rushbsq.h"

int	ft_atoi_header(char *str)
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

void	ft_parse_header(cf_map *map, char *line)
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
	map->lines = ft_atoi_header(line_temp);
}

int	validate_header(char *line)
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
	if (ft_atoi_header(line) == 0)
		return (0);
	return (1);
}




