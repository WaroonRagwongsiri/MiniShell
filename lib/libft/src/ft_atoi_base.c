/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:27:42 by pioncha2          #+#    #+#             */
/*   Updated: 2025/09/24 13:37:30 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	ft_check_base(char *str)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	if (len < 2)
		return (0);
	i = 0;
	while (i < len)
	{
		if (str[i] == '+' || str[i] == '-')
			return (0);
		j = i + 1;
		while (j < len)
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_get_base_idx(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	sum;
	int	sign;
	int	base_size;

	i = 0;
	sum = 0;
	sign = 1;
	if (!ft_check_base(base))
		return (0);
	base_size = ft_strlen(base);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && ft_get_base_idx(base, str[i]) >= 0)
	{
		sum = sum * base_size + ft_get_base_idx(base, str[i]);
		i++;
	}
	return (sum * sign);
}
