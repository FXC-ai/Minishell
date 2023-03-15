/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:36:30 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/15 17:57:41 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		string_has_right_redirection(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = count_chr(str, '>');
	return (count - 1);
}

int		string_has_left_redirection(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = count_chr(str, '<');
	return (count - 1);
}

void    handle_right_redirection(t_redirect redirection)
{
    
}

void	manage_redirection(char *str)
{
	int     right;
    int     left;
    char    **result;
    int     i;
    t_redirect redirection;

    i = 0;
    right = string_has_right_redirection(str);
    left = string_has_left_redirection(str);

    printf("Right %d, left %d\n", right, left);
    if (!right && !left)
        return ;
    while (right--)
    {
        result = ft_split_lexer(str, '>');
        redirection.left_str = result[i];
        redirection.right_str = result[i + 1];

        free(result[i]);
        free(result[i + 1]);
    }
    i = 0;
    while (left--)
    {
        result = ft_split_lexer(str, '<');
        redirection.left_str = result[i];
        redirection.right_str = result[i + 1];

        free(result[i]);
        free(result[i + 1]);
    }
}
