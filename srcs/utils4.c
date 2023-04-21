/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:53:34 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 14:42:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	init_utils(t_utils *u)
{
	u->i = 0;
	u->j = 0;
	u->in_quote = 0;
	u->in_word = 0;
	u->quote = '\0';
	u->start = 0;
	u->count = 0;
}