/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:23:47 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/26 10:54:26 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *)s;
	while (temp[i] != '\0')
	{
		if (temp[i] == (char)c)
			return (&temp[i]);
		i++;
	}
	if (temp[i] == (char)c)
		return (&temp[i]);
	return (NULL);
}

// DESCRIPTION
// 	The  strchr() function returns a pointer to the first occurrence of the
// 	character c in the string s.
//
// RETURN VALUE
// 	The strchr() and strrchr() functions return a pointer  to  the  matched
// 	character  or NULL if the character is not found.  The terminating null
// 	byte is considered part of the string, so that if  c  is  specified  as
// 	'\0', these functions return a pointer to the terminator.