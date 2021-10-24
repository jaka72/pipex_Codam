/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 16:43:41 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/10/30 16:43:41 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char *s;
	char *d;

	if (!dest && !src)
		return (NULL);
	s = (char*)src;
	d = (char*)dest;
	if (s < d)
	{
		s = s + len - 1;
		d = d + len - 1;
		while (len > 0)
		{
			*d = *s;
			d--;
			s--;
			len--;
		}
	}
	else
		return (ft_memcpy(d, s, len));
	return (dest);
}
