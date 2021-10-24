/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back..c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 20:01:25 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/26 20:01:25 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *newnode)
{
	t_list *temp;

	if (!*list)
	{
		*list = newnode;
		return ;
	}
	temp = *list;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newnode;
	newnode->next = NULL;
}
