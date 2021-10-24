/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:40:58 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/10/31 10:40:58 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *str, char c)
{
	char	*found;

	found = NULL;
	while (*str)
	{
		if (*str == c)
			found = (char*)str;
		str++;
	}
	if (c == '\0')
		return ((char*)str);
	return (found);
}
