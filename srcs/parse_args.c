/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:36:34 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/15 17:42:26 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"






void    parsing(char **args)
{
	int	i;

	i = 0;

	//execute_command(args[0], args[1]);
	while (args[i])
	{
		manage_redirection(args[i]);
		i++;
	}
	(void) args;
}