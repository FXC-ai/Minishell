/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:36:34 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/21 14:28:34 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    parsing(char **args)//ACUTALLY NOT A PARSING AT ALL
{
	int		i;
	i = 0;

	while (args[i])
	{
		//printf("args[i] = %s\n", args[i]);
		process_redirection(args[i]);
		//manage_redirection(args[i], &pipe);
		/*if (i != 0)
		{
			pipe->cmd2 = args[i + 1][0]; //QUAND L'INPUT EST BONNE
			//PIPE
		}*/
		i++;
	}
	(void) args;
}