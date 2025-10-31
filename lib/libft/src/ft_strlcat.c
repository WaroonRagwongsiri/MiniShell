/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:13:48 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/25 13:03:02 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (size <= d_len)
		return (s_len + size);
	i = 0;
	while (src[i] != '\0' && (i + d_len) < (size - 1))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (s_len + d_len);
}

// The strlcat() function appends the NUL-terminated string
// src to the end of dst.  It will append at most size -
// strlen(dst) - 1 bytes, NUL-terminating the result.
//
// append (size - len(dest) - 1) chars from src to dest
// return (len(src) + min(size, len(dest)))
