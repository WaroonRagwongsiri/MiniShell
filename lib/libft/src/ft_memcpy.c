/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:45:40 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/27 12:37:24 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*c_dest;
	char	*c_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	c_dest = (char *)dest;
	c_src = (char *)src;
	while (i < n)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (dest);
}

// DESCRIPTION
//        The memcpy() function copies n bytes from memory area src
//        to memory area dest.  The memory areas must not  overlap.
// RETURN VALUE
//        The memcpy() function returns a pointer to dest.