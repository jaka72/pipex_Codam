/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 21:51:17 by jmurovec      #+#    #+#                 */
/*   Updated: 2020/11/24 21:51:17 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*newnode;
	void	*newcontent;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	if (content != NULL)
	{
		newcontent = (void*)content;
		newnode->content = newcontent;
	}
	else
		newnode->content = NULL;
	newnode->next = NULL;
	return (newnode);
}
