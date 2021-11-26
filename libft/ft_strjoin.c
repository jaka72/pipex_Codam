/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 10:06:27 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/23 11:43:56 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	pt = malloc((len + 1) * sizeof(char));
	if (!pt)
		return (NULL);
	while (*s1)
	{
		*pt = *s1;
		pt++;
		s1++;
	}
	while (*s2)
	{
		*pt = *s2;
		pt++;
		s2++;
	}
	*pt = '\0';
	return (pt - len);
}
