/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:17:28 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/27 10:21:07 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		size;
	char	*arr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] != '\0' && ft_is_charset(s1[start], set))
		start++;
	while (end > start && ft_is_charset(s1[end], set))
		end--;
	size = end - start + 1;
	arr = malloc(size + 1);
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s1 + start, size);
	arr[size] = '\0';
	return (arr);
}

// Description
// Allocates memory (using malloc(3)) and returns a
// copy of ’s1’ with characters from ’set’ removed
// from the beginning and the end.