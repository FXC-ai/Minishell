/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:32:31 by vgiordan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/30 17:12:11 by fcoindre         ###   ########.fr       */
=======
/*   Updated: 2023/03/30 18:12:58 by vgiordan         ###   ########.fr       */
>>>>>>> cd06cd8fd347e36ffe5189d4e7f26f59383d1aa5
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	key_already_exist(char *key, char *env[])
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while ((env[i][j]) == key[j])
		{
			//printf("env[j][i] %c, key[i] %c", env[i][j], key[j]);
			j++;
		}
		if (j == (int) ft_strlen(key))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void add_to_env(char *ligne, char *value, char *env[])
{
   	int key_len = ft_strlen(ligne);
    int value_len = ft_strlen(value);
	char *result;
	int	i;
	int	j;
	char **s_result;

	s_result = ft_split(ligne, '=');
	unset_process_str(s_result[0], env);
	i = 0;
	j = 0;
	result = malloc(value_len + key_len + 2);

	

	while (i < key_len && ligne[i] != '=')
		result[j++] = ligne[i++];
	result[j++] = '=';
	i = 0;
	while (i < value_len)
	{
		result[j++] = value[i++];
	}
	result[j] = '\0';
	i = 0;
	while (env[i])
		i++;
	env[i] = result;
	env[i + 1] = NULL;
}

void export_process(char **current_command, char *env[])
{
	int i;
	char *equal_sign;
	char *value;
	char *key;

	i = 0;
	if (current_command[1] == NULL)
	{
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
	}
	else
	{
		equal_sign = strchr(current_command[1], '=');
       /*if (equal_sign == NULL) {
            fprintf(stderr, "export: invalid format, use KEY=VALUE\n");
            return;
        }*/
        key = current_command[1];
        value = ++equal_sign;

        add_to_env(key, value, env);
	}
}
