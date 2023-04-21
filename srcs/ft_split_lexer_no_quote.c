/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer_no_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:59:24 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 14:45:19 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	wtf(t_utils *u, const char *str)
{
	u->quote = str[u->i];
	u->in_quote = 1;
}

static int	count_chr_no_quote(const char *str)
{
	t_utils	u;

	init_utils(&u);
	while (str[u.i] != '\0')
	{
		if (u.in_word == 0 && u.in_quote == 0 && !is_space(str[u.i]))
		{
			if (is_quote(str[u.i]))
			{
				u.quote = str[u.i];
				u.in_quote = 1;
			}
			u.in_word = 1;
			u.count++;
		}
		else if (u.in_word == 1 && u.in_quote == 0 && is_quote(str[u.i]))
			wtf(&u, str);
		else if (u.in_word == 1 && u.in_quote == 1 && str[u.i] == u.quote)
			u.in_quote = 0;
		else if (u.in_word == 1 && u.in_quote == 0 && is_space(str[u.i]))
			u.in_word = 0;
		u.i++;
	}
	return (u.count);
}

static	int	process_while(t_utils *u, char const *str)
{
	if (u->in_word == 0 && u->in_quote == 0 && !is_space(str[u->i]))
	{
		if (is_quote(str[u->i]))
		{
			u->quote = str[u->i];
			u->in_quote = 1;
		}
		u->start = u->i;
		u->in_word = 1;
		return (1);
	}
	else if (u->in_word == 1 && u->in_quote == 0 && is_quote(str[u->i]))
	{
		u->quote = str[u->i];
		u->in_quote = 1;
		return (1);
	}
	else if (u->in_word == 1 && u->in_quote == 1 && str[u->i] == u->quote)
	{
		u->quote = '\0';
		u->in_quote = 0;
		return (1);
	}
	return (0);
}

static int	process(char const *str, char **result, int nb_word)
{
	t_utils	u;

	init_utils(&u);
	while (str[u.i] != '\0')
	{
		if (process_while(&u, str) == 0 && u.in_word == 1
			&& u.in_quote == 0 && is_space(str[u.i]))
		{
			u.in_word = 0;
			result[(u.j++)] = ft_substr(str, u.start, u.i - u.start);
		}
		(u.i++);
	}
	if (u.j < nb_word)
	{
		result[(u.j++)] = ft_substr(str, u.start, u.i - u.start);
	}
	result[u.j] = NULL;
	return (0);
}

char	**ft_split_lexer_no_quote(char *s)
{
	char	**result;
	int		r;
	int		nb_word;

	nb_word = count_chr_no_quote(s);
	result = malloc((nb_word + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	r = process(s, result, nb_word);
	if (r == -1)
		return (NULL);
	if (r == -2)
	{
		printf("Please close \" or \'\n");
		return (NULL);
	}
	free(s);
	return (result);
}
