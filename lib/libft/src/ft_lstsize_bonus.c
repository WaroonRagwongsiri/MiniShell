/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:19:02 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/26 12:30:56 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		size;

	curr = lst;
	size = 0;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

// Description 
// Counts the number of nodes in the list.