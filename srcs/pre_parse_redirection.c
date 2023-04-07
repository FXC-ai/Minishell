/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:53:27 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/07 13:59:50 by fcoindre         ###   ########.fr       */
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
        if (cmd[i] == '>')
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

char *delete_chevrons(char *cmd, int start, int end)
{

    char *str1;
    char *str2;
    char *tmp;
    char *result;
    int i;
    int j;

    int size_cmd;
    int size_str_chevrons;


    //printf("cmd = [%s]\n", cmd);

    size_cmd = ft_strlen(cmd);
    size_str_chevrons = end - start;

    result = malloc(sizeof(char)*(size_cmd - size_str_chevrons + 1));
    if (result == NULL)
    {
        return NULL;
    }

    i = 0;
    j = 0;
    while(cmd[i] != '\0')
    {
        if (i >= start && i <= end)
        {
            i++;
        }
        else
        {
            result[j] = cmd[i];
            i++;
            j++;
        }

    }


    return result;
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


void parse_redirection_right(char **tab_cmds)
{

    int start;
    int end;

    char *str2;
    char *str1;
    char *tmp;

    int nbr_chev;

    while(*tab_cmds)
    {
        nbr_chev = is_valid_chevron(*tab_cmds);
        while(nbr_chev > 0)
        {
            find_start_end(*tab_cmds, &start, &end);

            str2 = ft_strndup(*tab_cmds + start, (end - start));
            str1 = delete_chevrons(*tab_cmds, start, end);

            tmp = ft_strjoin(str1, " ");
            *tab_cmds = ft_strjoin(tmp, str2);


            nbr_chev--;
        }
        tab_cmds++;
    }



}



int main(void)
{
    char *cmd  = ">>c echo poire >b Mme >a | >>a >b >c echo poitr";
    char **result;

    result = ft_split_lexer(cmd, '|');
    normalize_with_space(result);
    print_tab(result);

    parse_redirection_right(result);

    print_tab(result);




    
    /*
    int start;
    int end;
    char *str_chevron;

    char *result_test;
    char *result_final;
    char *tmp;

    int nbr_chev;

    int index;

    index = 0;
    while(result[index])
    {
        nbr_chev = is_valid_chevron(result[index]);
        while(nbr_chev > 0)
        {
            find_start_end(result[index], &start, &end);

            str_chevron = ft_strndup(result[index] + start, (end - start));
            result_test = delete_chevrons(result[0], start, end);

            tmp = ft_strjoin(result_test, " ");
            result_final = ft_strjoin(tmp, str_chevron);

            result[index] = result_final;

            printf("result = [%s]\n", result_final);
            nbr_chev--;
        }
        index++;
    }*/
    // test = ft_strndup(result[0] + start, end);



    

    // printf("test = [%s]\n", test);
    // printf("result[0] + start = [%s]\n", result[0] + start);
    // printf("result[0] + end   = [%s]\n", result[0] + end);
    

    


    // ft_memmove(result[0] + start, result[0] + end, ft_strlen(result[0] + end));


    // printf("keep the hope : [%s]\n", result[0]);


    // test2 = ft_strjoin(result[0], test);


    // printf("keep the hope2 : [%s]\n", test2);





    /*Maintenant il faut coder la fonction qui modifie la str*/


    //size_next_wd(result[0]+1);
    //pre_parse_redirection(result);

    return 0;

}