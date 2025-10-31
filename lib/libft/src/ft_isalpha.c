/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pioncha2 <pioncha2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:02:40 by pioncha2          #+#    #+#             */
/*   Updated: 2025/08/25 10:23:42 by pioncha2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

// isalpha()
// checks  for an alphabetic character; in the standard "C" locale,
// it is equivalent to (isupper(c) ||  islower(c)).   In  some  lo‐
// cales, there may be additional characters for which isalpha() is
// true—letters which are neither uppercase nor lowercase.
