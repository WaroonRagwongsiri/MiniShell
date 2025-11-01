/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:33:52 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/01 20:08:28 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c_sep)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (str == NULL)
		return (0);
	if (c_sep == '\0')
		return (1);
	if (str[i] != c_sep)
	{
		cnt++;
		i++;
	}
	while (str[i] != '\0' && str[i] == c_sep)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] != c_sep && str[i - 1] == c_sep)
			cnt++;
		i++;
	}
	return (cnt);
}

static char	*ft_spliter(const char *str, char c_sep, int start_idx)
{
	int		i;
	int		size;
	char	*word;

	i = start_idx;
	size = 0;
	while (str[i] != '\0' && str[i] != c_sep)
	{
		i++;
		size++;
	}
	word = ft_safe_calloc(size + 1, sizeof(char), "");
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = str[start_idx + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static	char	**ft_empty_arr(void)
{
	char	**arr;

	arr = ft_safe_calloc(1, sizeof(char *), "");
	arr[0] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**arr;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
		return (ft_empty_arr());
	size = ft_count_words(s, c);
	arr = ft_safe_calloc(size + 1, sizeof(char *), "");
	if (arr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		arr[i] = ft_spliter(s, c, j);
		j += ft_strlen(arr[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// Description 
// Allocates memory (using malloc(3)) and returns an
// array of strings obtained by splitting ’s’ using
// the character ’c’ as a delimiter. The array must
// end with a NULL pointer.

// #include <stdio.h>
//
// size_t	ft_strlen(const char *s)
// {
// 	int	i;
//
// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
//
// int	main(void)
// {
// 	char **tab = ft_split("  tripouille  42  ", ' ');
//
// 	tab = ft_split("tripouille", 0);
//
// 	int i;
// 	i = 0;
// 	while (tab[i] != NULL)
// 	{
// 		printf("tab[%d] : %s\n", i, tab[i]);
// 		i++;
// 	}
//
// }
