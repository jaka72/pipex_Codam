/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 21:51:17 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/24 21:51:17 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **list, void (*del_cont)(void *))
{
	t_list	*temp;

	if (!del_cont || !list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = temp->next;
		ft_lstdelone(temp, del_cont);
	}
	*list = NULL;
}
