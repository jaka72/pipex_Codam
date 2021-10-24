/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 21:51:17 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/24 21:51:17 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstiter(t_list *list, void (*f)(void *node))
{
	t_list *temp;

	temp = list;
	if (!list || !f)
		return ;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}
