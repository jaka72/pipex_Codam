/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:32:48 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/10/31 10:32:48 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	if (c == '\0')
		return (str + ft_strlen(s));
	while (*str)
	{
		if (c == *str)
			return (str);
		str++;
	}
	return (NULL);
}
