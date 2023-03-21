/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/21 17:04:31 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void disable_ctrl_chars() {
    struct termios term_attrs;

    // Récupérer les attributs actuels du terminal
    tcgetattr(STDIN_FILENO, &term_attrs);

    // Désactiver l'affichage des caractères de contrôle pour Ctrl+C, Ctrl+D et Ctrl+ '\'
    //term_attrs.c_lflag &= ECHOCTL;

    // Appliquer les nouveaux attributs au terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &term_attrs);
}

int	check_entry(char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (0);
	add_history(line);
	if (ft_strncmp(line, " ", ft_strlen(line)) == 0)
		return (0);
	return (1);
}

void	wait_for_input(char *env[])
{
	char    *line;
	while(42)
	{
		line = readline("$ ");
		if (line == NULL)
		{
			printf("exit\n");
            break;
        }
		if (check_entry(line))
		{
			lexer(line, env);
		}
	}
}

char **e;
int	main(int ac, char **argv, char *env[])
{
	(void) argv;
	(void) ac;
	e = env;
	//disable_ctrl_chars();
	signal_handler();
	wait_for_input(env);
	return (0);
}