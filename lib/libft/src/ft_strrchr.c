/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:09:22 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/26 11:30:05 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*output;
	char	*temp;

	i = 0;
	output = NULL;
	temp = (char *)s;
	while (temp[i] != '\0')
	{
		if (temp[i] == (char)c)
			output = &temp[i];
		i++;
	}
	if (temp[i] == (char)c)
		return (&temp[i]);
	return (output);
}

// DESCRIPTION

// 	The strrchr() function returns a pointer to the last occurrence of  the
// 	character c in the string s.
//
// RETURN VALUE
// 	The strchr() and strrchr() functions return a pointer  to  the  matched
// 	character  or NULL if the character is not found.  The terminating null
// 	byte is considered part of the string, so that if  c  is  specified  as
// 	'\0', these functions return a pointer to the terminator.
