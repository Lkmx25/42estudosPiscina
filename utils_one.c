
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

void	swap_pointer(int *curr, int *prev)
{
	int	*temp;

	temp = prev;
	prev = curr;
	curr = temp;
}

int	ft_min(int a, int b, int c)
{
	if (a < b && a < c)
		return (a);
	if (b < a && b < c)
		return (b);
	if (c < a && c < b)
		return (c);
	return(0);
}