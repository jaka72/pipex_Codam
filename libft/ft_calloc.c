/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 11:33:09 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/10/22 13:07:03 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	char	*pt;

	if (size && (SIZE_MAX / size) < count)
		return NULL;

	pt = malloc(count * size);
	if (!pt)
		return (NULL);
	pt = ft_memset(pt, 0, count * size);
	return (pt);
}
