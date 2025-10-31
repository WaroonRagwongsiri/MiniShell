/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:09:54 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 15:26:33 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_safe_calloc(size_t nmemb, size_t size, char *cmd)
{
	static t_list	*mem_lst = NULL;
	t_list			*new;
	void			*ptr;

	if (cmd == NULL)
	{
		ft_lstclear(&mem_lst, free);
		return (NULL);
	}
	new = ft_lstnew(NULL);
	if (!new)
		return (NULL);
	ft_lstadd_back(&mem_lst, new);
	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	new->content = ptr;
	return (ptr);
}
