/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:29:08 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/25 15:10:17 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] != '\0' && big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return (&((char *)big)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// DESCRIPTION
// 	The strnstr() function locates the first occurrence of the null-termi‐
// 	nated string little in the string big, where not more than len characters
// 	are searched.  Characters that appear after a ‘\0’ character are not
// 	searched.  Since the strnstr() function is a FreeBSD specific API, it
// 	should only be used when portability is not a concern.
//
// RETURN VALUES
// 	If little is an empty string, big is returned; if little occurs nowhere
// 	in big, NULL is returned; otherwise a pointer to the first character of
// 	the first occurrence of little is returned.