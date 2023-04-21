/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:17:15 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 16:27:24 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		exit(errno);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	p1(char *s, char **result, t_utils *u)
{
	if (u->j < u->count)
		result[u->j++] = word_dup(s, u->start, u->i);
	while (s[u->i + 1] && s[u->i + 1] == ' ' && !u->in_quote)
		u->i++;
	u->start = u->i + 1;
}

static int	process(char *s, char **result, char c)
{
	t_utils	u;

	init_utils(&u);
	u.count = count_chr(s, c);
	while (s[u.i])
	{
		if ((s[u.i] == '\'' || s[u.i] == '\"') && !u.in_quote)
		{
			u.in_quote = 1;
			u.quote = s[u.i];
		}
		else if ((s[u.i] == '\'' || s[u.i] == '\"')
			&& u.in_quote && s[u.i] == u.quote)
			u.in_quote = 0;
		else if (!u.in_quote && s[u.i] == c)
			p1(s, result, &u);
		u.i++;
	}
	if (u.in_quote == 1)
		return (-2);
	if (!u.in_quote && u.j < u.count)
		result[u.j++] = word_dup(s, u.start, u.i);
	result[u.j] = NULL;
	return (0);
}

char	**ft_split_lexer(char *s, char c)
{
	char	**result;
	int		r;

	result = malloc((count_chr(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	r = process(s, result, c);
	if (r == -1)
		return (NULL);
	if (r == -2)
	{
		printf("Please close \" or \'\n");
		return (NULL);
	}
	return (result);
}
