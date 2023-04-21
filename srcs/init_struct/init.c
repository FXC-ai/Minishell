/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:09:14 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 17:57:51 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_parsed_args	**init_parsed_args(char **tab_cmds)
{
	t_parsed_args	**list_struct;
	t_parsed_args	*current_struct;
	char			**tmp;
	int				i;

	list_struct = malloc((size_tab(tab_cmds) + 1) * sizeof(t_parsed_args *));
	if (list_struct == NULL)
		return (NULL);
	i = 0;
	while (tab_cmds[i])
	{
		current_struct = malloc(sizeof(t_parsed_args));
		if (current_struct == NULL)
			return (NULL);
		tmp = separate_command(tab_cmds[i]);
		current_struct->cmd_args
			= ft_split_lexer_no_quote(concatenate_strings_with_spaces(tmp));
		remove_quote_in_tab(current_struct->cmd_args);
		freemalloc(tmp, size_tab(tmp));
		current_struct->redirections = separate_redirections(tab_cmds[i]);
		list_struct[i] = current_struct;
		i++;
	}
	list_struct[i] = NULL;
	return (list_struct);
}
