/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:20:17 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/26 10:48:20 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		if (temp[i] == (unsigned char)c)
			return ((void *) &temp[i]);
		i++;
	}
	return (NULL);
}

// DESCRIPTION
// 	The  memchr()  function  scans  the  initial n bytes of the memory area
// 	pointed to by s for the first instance of c.  Both c and the  bytes  of
// 	the memory area pointed to by s are interpreted as unsigned char.

// RETURN VALUE
// 	The  memchr()  and memrchr() functions return a pointer to the matching
// 	byte or NULL if the character does not occur in the given memory area.
