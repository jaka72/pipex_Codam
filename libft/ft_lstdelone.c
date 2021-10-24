/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 15:58:00 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/26 15:58:00 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list *list, void (*del_list)(void *))
{
	if (!list)
		return ;
	if (del_list)
		del_list(list->content);
	free(list);
}
