#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

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
    char c_debug;

	count = 0;
	i = 0;
	in_quote = 0;
	quote = '\0';
	in_word = 0;
	while (str[i] != '\0')
	{
        c_debug = str[i];
		/*if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = str[i];
				in_quote = 1;
			}
			else if (str[i] == quote)
			{
				quote = '\0';
				in_quote = 0;
			}
			//printf("quote = %c in_quote = %d\n", quote, in_quote);
		}*/
        if (in_word == 0 && in_quote == 0)
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
            count++;
        }
        else if (in_word == 1 && in_quote == 1 && str[i] == quote)
        {
            quote = '\0';
            in_quote = 0;
            in_word = 0;
        }

		else if (in_word == 1 && in_quote == 0 && is_space(str[i]))
		{
			in_word = 0;
		}
        printf("count = %d | str[%d] = %c : in_word = %d, in_quote = %d, quote = %c\n",count,i, str[i], in_word, in_quote, quote);

		i++;
	}


	/*while (str[i] != '\0')
	{
		if (str[i] == c && in_quote == 0)
		{
			count++;
		}
		if (is_quote(str[i]) == 1 && in_quote == 0)
		{
			in_quote = 1;
			quote = str[i];
			i++;
		}
		if (str[i] == quote && in_quote == 1)
		{
			in_quote = 0;
			quote = '\0';
		}
		i++;
	}
	if (str[i-1] != c)
	{
		count++;
	}*/
	printf("Nombre de mot %d\n", count);
	return count;
}



int main(int argc, char const *argv[])
{

    const char *str = "echo \"p\"p";
	char *str2 = "Hello";
	char str3[] = "Hello\0";

	//str2[2] = '1';
	str3[2] = '1';
	printf("%s\n", str2);
	printf("%s\n", str3);

    int count = count_chr_no_quote(str);

    return 0;
}
