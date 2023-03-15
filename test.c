#include "includes/header.h"

static int  is_quote(char c)
{
    return (c == '\'' || c == '"');
}

static int count_words(char *str)
{
    int i = 0;
    int count = 0;
    int in_quotes = 0;
    int in_word = 0;
    char quote_char = '\0';
    while(str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        
        while (str[i] && is_quote(str[i]) == 0)
        {
            in_word = 1;
            i++;
            
        }
        quote_char = str[i];
        if(str[i])
        {
            in_quotes = 1;
            i++;
        }
            
        while (str[i] && str[i] != quote_char)
        {
            i++;
        }
        if(str[i])
            i++;
        count += (in_quotes + in_word);
        in_quotes = 0;
        in_word = 0; 
    }
    return (count);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

/*static void	freemalloc(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		result[j] = NULL;
		j--;
	}
	free(result);
}*/

static int process(char *str, char **result)
{
    int i = 0;
    int j = 0;
    int words_count;
    int start;
    char quote_char = '\0';
    char *check_result;

    words_count = count_words(str);
    printf("count %d\n", words_count);
    while(str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        start = i;
        while (str[i] && is_quote(str[i]) == 0)
        {
            i++;
        }
        if (start < i)
        {
            result[j++] = word_dup(str, start, i);
            check_result = result[j-1];
        }
        quote_char = str[i];
        if(str[i])
        {
            i++;
        }
        start = i;
        while (str[i] && str[i] != quote_char)
        {
            i++;
        }
        if (start < i)
        {
            result[j++] = word_dup(str, start-1, i+1);
            check_result = result[j-1];
        }
        if(str[i])
            i++;
    }
    result[j] = NULL;
    return (0);
}



char	**ft_split_lexer(char *s)
{
	char	**result;

	result = malloc((count_words(s) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (process(s, result) == -1)
		return (NULL);
	return (result);
}


char **lexer(char *str)
{
	char	**result;
	int		i;

	i = 0;
	/*if (count_char(str, '\'') % 2 || count_char(str, '"') % 2)
	{
		my_error();
	}*/
	result = ft_split_lexer(str);
	while (result[i])
	{
		printf("str %d = [%s]\n", i, result[i]);
		i++;
	}
	return (result);
}


int main(int argc, char const *argv[])
{
    char *str = "''";
    char *str1 = "sssssssss";
    char *str2 = "1ssssssss sssss";
    char *str3 = "     1ssssssss   n\"2s\" sadakshdsalhdljsahls 'kljlk' 'jjuuju' ";
    char *str4 = "    11111 22222";
    char *str5 = "   \"111\"  \"222\"  \"333\"  llkjlkj lkjlkjlkj lkjlkj ";
    char *str6 = " '11\"1'   '222'  '333'   ";
    char *str7 = "   \" 111''''''''''' \"   ''  '  2222 ' \"\" ' 3333\"333 '   ";

    
    printf("\nTEST = %s\n", str);
    lexer(str);
    
    
    printf("\nTEST = %s\n", str1);
    lexer(str1);

    
    printf("\n TEST = %s\n", str2);
    lexer(str2);

    printf("\n TEST = %s\n", str3);
    lexer(str3);

    printf("\n TEST = %s\n", str4);
    lexer(str4);

    printf("\n TEST = %s\n", str5);
    lexer(str5);

    printf("\n TEST = %s\n", str6);
    lexer(str6);

    printf("\n TEST = %s\n", str7);
    lexer(str7);
    
    return 0;
}
