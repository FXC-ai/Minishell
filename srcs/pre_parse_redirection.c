/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:53:27 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/06 18:38:08 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"

static int is_chevron (char c)
{

    return c == '>' || c == '<';

}

int size_next_wd(char *str)
{
    
    int size_wd;

    size_wd = 0;

    while(*str && is_space(*str) == 1)
    {
        str++;
    }

    while(*str && is_space(*str) == 0)
    {
        size_wd++;
        str++;
    }

    printf("size_wd = %d\n", size_wd);

    return size_wd;
}

int is_valid_chevron (char *cmd)
{
    int j;
    int count;

    count = 0;
    j = 0;
    while (*cmd != '\0')
    {
        if (*cmd == '>')
        {
            if (*(cmd+1) == '>')
            {
                cmd+=1;
            }
            cmd++;
            while (is_space(*cmd) == 1)
            {
                cmd++;
            }
            if (is_chevron(*cmd) == 1)
            {
                return -1;
            }
            count++;
        }
        cmd++;
    }
    return count;
}

void find_start_end(char *cmd, int *start, int *end)
{
    int i;

    i = 0;
    *end = 0;
    *start = 0;

    while (cmd[i])
    {
        if (*cmd == '>')
        {
            *start = i;
            if (cmd[i+1] == '>')
            {
                i++;
            }
            i++;
            while (is_space(cmd[i]) == 1)
            {
                i++;
            }
            while (ft_isalnum(cmd[i]))
            {
                i++;
            }
            *end = i;
            break;
        }
        i++;
    }
}


/*
void pre_parse_redirection(char *tab_cmds)
{
    printf("string to manage : %s\n", tab_cmds[0]);

    int size_wd;
    char *new_str = NULL;
    char *tmp = NULL;
    char *cheuv;
    int j;

    size_wd = 0;

    j = 0;
    while (tab_cmds[0][j] != '\0' && tab_cmds[0][j] != '>')
    {
        j++;
    }

    if (tab_cmds[0][j+1] == '>')
    {
        cheuv = ">>";
        j++;
    }
    else
    {
        cheuv = ">";
    }

    j++;
    while (tab_cmds[0][j] != '\0' && is_space(tab_cmds[0][j]) == 1)
    {
        j++;
    }

    if (tab_cmds[0][j] == '>' || tab_cmds[0][j] == '\0')
    {
        return; // CAS ou ou il y a une erreur de type ".... >   > ...." ou " ....  >"
    }


    size_wd = size_next_wd(tab_cmds[0]+j);

    tmp = ft_strndup(tab_cmds[0]+j, size_wd);

    new_str = ft_strjoin(cheuv, tmp);

}
*/




int main(void)
{

    char *cmd  = ">>p >> 7>abc bonjour >>echo bonjour > >b \"Mr\" > c \"Mme\"";
    char **result;
    int start;
    int end;

    char *test;

    int nbr_chev;

    result = ft_split_lexer(cmd, '|');

    normalize_with_space(result);

    print_tab(result);

    nbr_chev = is_valid_chevron(cmd);

    find_start_end(result[0], &start, &end);

    printf("start = %d || end = %d\n",start, end);


    test = ft_strndup(result[0] + start, end);

    printf("test = [%s]\n", test);

    /*Maintenant il faut coder la fonction qui modifie la str*/


    //size_next_wd(result[0]+1);
    //pre_parse_redirection(result);

    return 0;

}