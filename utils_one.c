/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:04:27 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 20:04:28 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rushbsq.h"

int	ft_is_digit(char c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_printable(char c)
{
	if (!(c >= 32 && c <= 126))
		return (0);
	return (1);
}

int	compare_char(char a, char b, char c)
{
	if (c == b || c == a || b == a)
		return (0);
	return (1);
}

void	swap_pointer(int **curr, int **prev)
{
	int	*temp;

	temp = *prev;
	*prev = *curr;
	*curr = temp;
}
