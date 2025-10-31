/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:11:40 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/25 13:16:44 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*arr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = malloc(s1_len + s2_len + 1);
	if (arr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		arr[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		arr[i++] = s2[j++];
	arr[i] = '\0';
	return (arr);
}

// Description 
// Allocates memory (using malloc(3)) and returns a
// new string, which is the result of concatenating
// ’s1’ and ’s2’.