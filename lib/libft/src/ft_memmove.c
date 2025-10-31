/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:59:05 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/27 10:20:12 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*c_dest;
	char	*c_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	c_dest = (char *)dest;
	c_src = (char *)src;
	if (c_dest > c_src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			c_dest[i] = c_src[i];
		}
	}
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}

// DESCRIPTION
// 	The  memmove()  function  copies n bytes from memory area
// 	src to memory area dest.  The memory areas  may  overlap:
// 	copying  takes place as though the bytes in src are first
// 	copied into a temporary array that does not  overlap  src
// 	or dest, and the bytes are then copied from the temporary
// 	array to dest.

// RETURN VALUE
// 	The memmove() function returns a pointer to dest.