/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:42:22 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/25 15:06:17 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*arr;
	int		i;

	size = ft_strlen(s);
	arr = malloc(size + 1);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

// DESCRIPTION
// 	The  strdup() function returns a pointer to a new string which is a du‐
// 	plicate of the string s.  Memory for the new string  is  obtained  with
// 	malloc(3), and can be freed with free(3).
//
// RETURN VALUE
// 	On  success,  the strdup() function returns a pointer to the duplicated
// 	string.  It returns NULL if insufficient memory was available, with er‐
// 	rno set to indicate the cause of the error.
