/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 21:51:17 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/24 21:51:17 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_front(t_list **list, t_list *newnode)
{
	if (!*list)
	{
		*list = newnode;
		return ;
	}
	if (!newnode)
		return ;
	newnode->next = *list;
	*list = newnode;
}
