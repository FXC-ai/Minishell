/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:36:34 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/24 16:13:23 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
void    parsing(char **args, char *env[])//ACUTALLY NOT A PARSING AT ALL
{
	int		i;
	i = 0;
	/*printf("args[0] %s\n", args[0]);
	printf("args[1] %s\n", args[1]);
	printf("args[2] %s\n", args[2]);*/

	char *tab[2];
	
	
	tab[0] = args[0];
	tab[1] = args[1];
	ms_pipe(tab, env);
	//process_redirection(args[0], env);
	//printf("Done\n");




	//{
		//printf("args[i] = %s\n", args[i]);
		
		//process_redirection(args[i]);
		//manage_redirection(args[i], &pipe);
		/*if (i != 0)
		{
			pipe->cmd2 = args[i + 1][0]; //QUAND L'INPUT EST BONNE
			//PIPE
		}*/
		i++;
	//}
	(void) args;
}