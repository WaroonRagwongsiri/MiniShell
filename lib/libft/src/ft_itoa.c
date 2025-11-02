/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:57:17 by pioncha2          #+#    #+#             */
/*   Updated: 2025/11/02 09:09:27 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	int		cnt;
	long	nbr;

	cnt = 0;
	nbr = n;
	if (nbr <= 0)
	{
		cnt++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		cnt++;
		nbr /= 10;
	}
	return (cnt);
}

static char	*ft_create_arr(int n)
{
	int		size;
	char	*arr;

	size = ft_get_size(n);
	arr = ft_safe_calloc(size + 1, sizeof(char), "");
	if (arr == NULL)
		return (NULL);
	arr[size] = '\0';
	if (n == 0)
	{
		arr[0] = '0';
		return (arr);
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}

char	*ft_itoa(int n)
{
	int		size;
	int		i;
	char	*arr;
	long	nbr;

	size = ft_get_size(n);
	arr = ft_create_arr(n);
	if (arr == NULL)
		return (NULL);
	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	i = size - 1;
	while (nbr > 0)
	{
		arr[i] = (nbr % 10) + '0';
		i--;
		nbr /= 10;
	}
	return (arr);
}

// Description 
// Allocates memory (using malloc(3)) and returns
// a string representing the integer received as an
// argument. Negative numbers must be handled.