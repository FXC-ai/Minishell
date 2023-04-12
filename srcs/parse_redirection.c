/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:53:27 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/12 17:01:55 by vgiordan         ###   ########.fr       */
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

    return size_wd;
}

static int is_valid_chevron (char *cmd)
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

static void find_start_end(char *cmd, int *start, int *end)
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

static char *delete_chevrons(char *cmd, int start, int end)
{

    char *result;
    int i;
    int j;

    int size_cmd;
    int size_str_chevrons;

    int size_result;

    size_cmd = ft_strlen(cmd);
    size_str_chevrons = end - start;
    size_result = size_cmd - size_str_chevrons + 1;

    result = malloc(sizeof(char)*(size_cmd - size_str_chevrons + 1));
    if (result == NULL)
    {
        return NULL;
    }

    i = 0;
    j = 0;
    while(j < size_result)
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
    result[j] = '\0';
    return result;
}


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
        //printf("nbr_chev = %d\n", nbr_chev);

        while(nbr_chev > 0)
        {
            find_start_end(*tab_cmds, &start, &end);

            

            str2 = ft_strndup(*tab_cmds + start, (end - start));

            printf("str2 = [%s]\n", str2);

            str1 = delete_chevrons(*tab_cmds, start, end);

            printf("str1 = [%s]\n", str1);

            tmp = ft_strjoin(str1, " ");
            free(*tab_cmds);
            *tab_cmds = NULL;
            
            *tab_cmds = ft_strjoin(tmp, str2);

            printf("tab_cmds = [%s]\n\n", *tab_cmds);

            free(tmp);
            tmp = NULL;
            free (str1);
            free (str2);


            nbr_chev--;
        }
        tab_cmds++;
    }

}

/*
void parse_redirection_left (char **tab_cmds)
{

    
        // valider le nombre de chevrons
        // parcourir la commande depuis la fin
        // chaque fois qu un chevron < ou << est trouve
        //     le supprimer de la chaine
        //     le mettre en debut de chaine
    


    int start;
    int end;

    char *str2;
    char *str1;
    char *tmp;

    int nbr_chev;
    int nbr_chev_cpy;

    int i;
    int j;


    while(*tab_cmds)
    {
        nbr_chev = is_valid_chevron(*tab_cmds, '<');
        nbr_chev_cpy = nbr_chev;
        while (nbr_chev_cpy > 0)
        {
            i = 0;
            j = 0;
            while (j < nbr_chev - 1)
            {
                if (*(*tab_cmds + i) == '<')
                {
                    j++;
                    if (*(*tab_cmds + i + 1) == '<')
                    {
                        i++;
                    }
                }
                i++;
            }

            find_start_end(*tab_cmds + i, &start, &end, '<');

            str2 = ft_strndup(*tab_cmds + i + start, end - start);

            //printf("str2 = %s\n", str2);


            str1 = delete_chevrons(*tab_cmds, start + i, end + i);

            //printf("str1 = %s\n", str1);

            tmp = ft_strjoin(str2, str1);


            *tab_cmds = tmp;
            //printf("tmp = %s\n", tmp);
            nbr_chev_cpy--;
        }
        tab_cmds++;
    }

}
*/


// int main(void)
// {
//     //char *cmd  = ">>c echo  poire >b Mme >a | <<a echo poitr <b | echo bonjour <<END <a >>b >C | echo bonjour < <END <a >>b >C";
//     char *cmd  = ">>   0 >a echo > b bonjour > ccc >>gg hello";
//     char **result;

//     result = ft_split_lexer(cmd, '|');
//     normalize_with_space(result);
//     print_tab(result);

//     parse_redirection_right(result);
//     //parse_redirection_left(result);


//     print_tab(result);

//     freemalloc(result, size_tab(result));

//     return 0;

// }