/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 11:26:11 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/02 11:26:11 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_getlen(long n)
{
	int len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	insert_digits(int len, char *pt, long n)
{
	while (len >= 0)
	{
		pt[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*pt;
	int		len;
	long	abs_n;

	abs_n = n;
	len = 0;
	if (abs_n < 0)
	{
		abs_n *= -1;
		len++;
	}
	len += ft_getlen(abs_n);
	pt = malloc(sizeof(char) * (len + 1));
	if (!pt)
		return (NULL);
	pt[len] = '\0';
	len--;
	insert_digits(len, pt, abs_n);
	if (n < 0)
		pt[0] = '-';
	return (pt);
}
