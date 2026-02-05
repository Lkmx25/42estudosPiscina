/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkenji-s <lkenji-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:07:31 by lkenji-s          #+#    #+#             */
/*   Updated: 2026/02/04 20:07:41 by lkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

int		ft_is_digit(char c);
int		ft_strlen(char *str);
int		ft_is_printable(char c);
int		compare_char(char a, char b, char c);
void	swap_pointer(int **curr, int **prev);
int		ft_min(int a, int b, int c);

#endif