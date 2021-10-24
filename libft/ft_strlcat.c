/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 22:26:46 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/10/30 22:26:46 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dest);
	if (size < ft_strlen(dest))
		len = size;
	i = 0;
	while (src[i] != '\0' && size > len + i + 1)
	{
		dest[len + i] = src[i];
		i++;
	}
	if (size > len + i)
		dest[len + i] = '\0';
	return (len + ft_strlen(src));
}
