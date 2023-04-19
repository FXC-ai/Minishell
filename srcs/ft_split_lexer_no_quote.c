/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer_no_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:59:24 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 12:33:15 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int  is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int count_chr_no_quote(const char *str)
{
	int count;
	int i;
	int in_quote;
	char quote;
	int in_word;

	count = 0;
	i = 0;
	in_quote = 0;
	quote = '\0';
	in_word = 0;
	while (str[i] != '\0')
	{
		
        if (in_word == 0 && in_quote == 0 && !is_space(str[i]))
        {
            if (is_quote(str[i]))
            {
                quote = str[i];
                in_quote = 1;
            }
            in_word = 1;
            count++;
        }
        else if (in_word == 1 && in_quote == 0 && is_quote(str[i]))
        {
            quote = str[i];
            in_quote = 1;
            //count++;
        }
        else if (in_word == 1 && in_quote == 1 && str[i] == quote)
        {
            quote = '\0';
            in_quote = 0;
            //in_word = 0;
        }
		else if (in_word == 1 && in_quote == 0 && is_space(str[i]))
		{
			in_word = 0;
		}
        //printf("count = %d | str[%d] = %c : in_word = %d, in_quote = %d, quote = %c\n",count,i, str[i], in_word, in_quote, quote);

		i++;
	}
	//printf("Nombre de mot %d\n", count);
	return count;
}

static int process(char const *str, char **result, int nb_word)
{
    int i = 0;
    int j = 0;
    int start = 0;
    int in_quote = 0;
    char quote = '\0';
    int in_word = 0;

	while (str[i] != '\0')
	{
        //printf("sdfsdffsddfs\n");
        //printf("%d [%c] in quote = [%d], quote = [%c], in_word = [%d]\n", i, str[i], in_quote, quote, in_word);
        if (in_word == 0 && in_quote == 0 && !is_space(str[i]))
        {
            if (is_quote(str[i]))
            {
                quote = str[i];
                in_quote = 1;
            }
            start = i;
            in_word = 1;
        }
        else if (in_word == 1 && in_quote == 0 && is_quote(str[i]))
        {
            quote = str[i];
            in_quote = 1;
            //result[j++] = ft_substr(str, start, i - start);
            //start = i;
            //printf("result[%d] = [%s]\n", j-1, result[j-1]);
        }
        else if (in_word == 1 && in_quote == 1 && str[i] == quote)
        {
            quote = '\0';
            in_quote = 0;
            //in_word = 0;
            //result[j++] = ft_substr(str, start, i - start + 1);//EDITTTTTTTTTTTTT
            //printf("result[%d] = [%s]\n", j-1, result[j-1]);
        }
		else if (in_word == 1 && in_quote == 0 && is_space(str[i]))
		{
			in_word = 0;
            result[j++] = ft_substr(str, start, i - start);
            //printf("result[%d] = [%s]\n", j-1, result[j-1]);
		}
		i++;
        
	}
    
    //printf("Nb word %d\n", nb_word);
    //printf("nb_word = %d j = %d\n", nb_word, j);
    if (j < nb_word)
        result[j++] = ft_substr(str, start, i - start);
    result[j] = NULL;
    return (0);
}

char	**ft_split_lexer_no_quote(char *s)
{
	char	**result;
	int     r;
    int nb_word;

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
    print_tab("Result", result);
	return (result);
}
