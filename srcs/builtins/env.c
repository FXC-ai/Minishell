/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:52 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 11:11:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	env_process(char **parsed_args)
{
	int	i;

	if (size_tab(parsed_args) == 1)
	{
		i = 0;
		while (g_env.env[i])
		{
			printf("%s\n", g_env.env[i++]);
		}
	}
	else
	{
		g_env.ms_errno = 127;
		perror("env");
	}
}
