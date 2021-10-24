/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 09:54:14 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/18 18:17:05 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	char	*pt;
	//size_t	i;
	char	*sss;

	if (!s)
		return (NULL);
	if (n > ft_strlen(s))
		n = ft_strlen(s);
	pt = malloc((n + 1) * sizeof(char));
	if (!pt)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		pt[0] = '\0';
		return (pt);
	}
	//i = 0;
	sss = (char*)s + start;
/*	while (i < n && s[start] != '\0')
	{
		pt[i] = s[start];
		i++;
		start++;
	}
	pt[i] = '\0';
*/
	ft_strlcpy(pt, sss, n + 1);
	return (pt);
}
