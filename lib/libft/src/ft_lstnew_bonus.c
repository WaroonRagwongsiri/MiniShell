/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:09:24 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/26 12:13:51 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->content = content;
	return (new);
}

// Description 
// Allocates memory (using malloc(3)) and returns
// a new node. The ’content’ member variable is
// initialized with the given parameter ’content’.
// The variable ’next’ is initialized to NULL.