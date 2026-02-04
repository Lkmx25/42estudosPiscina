int	first_line_dp(char *line, cf_map *config, t_dyp *dynamic)
{
	if (!first_line_validation(config, line))
		return (0);
	config->cols = ft_strlen(line);
	dynamic->curr_row = (int *)malloc(sizeof(int) * config->cols);
	if (!dynamic->curr_row)
		return (0);
	dynamic->prev_row = (int *)malloc(sizeof(int) * config->cols);
	if (!dynamic->prev_row)
	{
		free(dynamic->curr_row);
		return (0);
	}
	translate_map(line, config, dynamic, 0);
	swap_pointer(&dynamic->curr_row, &dynamic->prev_row);
	return (1);
}
