/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:26:20 by waragwon          #+#    #+#             */
/*   Updated: 2025/10/31 16:30:04 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_safe_calloc(-1, -1, NULL);
	exit(EXIT_FAILURE);
}
