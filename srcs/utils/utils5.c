/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:00:01 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/02 16:00:07 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	wait_all_process(int nbr_cmd, int *status)
{
	int	i;

	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(-1, status, 0);
		if (WIFEXITED(*status))
		{
			g_env.ms_errno = WEXITSTATUS(*status);
		}
		i++;
	}
}

void	init_in_out(int **in_out_fd)
{
	(*in_out_fd)[0] = STDIN_FILENO;
	(*in_out_fd)[1] = STDOUT_FILENO;
}
