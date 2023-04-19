/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:32:31 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 14:47:32 by vgiordan         ###   ########.fr       */
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

void	add_to_env(char *ligne, char *value, char *env[])
{
	char	*result;
	int		i;
	int		j;
	char	**s_result;

	s_result = ft_split(ligne, '=');
	unset_process_str(s_result[0], env);
	i = 0;
	j = 0;
	result = malloc(ft_strlen(value) + ft_strlen(ligne) + 2);
	while (i < (int)ft_strlen(ligne) && ligne[i] != '=')
		result[j++] = ligne[i++];
	result[j++] = '=';
	i = 0;
	while (i < (int)ft_strlen(value))
		result[j++] = value[i++];
	result[j] = '\0';
	i = 0;
	while (env[i])
		i++;
	env[i] = result;
	env[i + 1] = NULL;
	freemalloc(s_result, size_tab(s_result));
}

void	print_export(char *env[])
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j] && env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		if (env[i][j] == '=')
		{
			printf("=");
			printf("\"");
			j++;
			while (env[i][j])
				printf("%c", env[i][j++]);
		}
		printf("\"");
		printf("\n");
		i++;
	}
}

void	export_process(char **current_c, char *env[])
{
	int		i;
	char	*equal_sign;
	char	*value;
	char	*key;

	i = 0;
	if (current_c[1] == NULL)
		print_export(env);
	else
	{
		while (current_c[1][i] != '\0' && current_c[1][i] != '=')
		{
			if (ft_isalnum(current_c[1][i]) == 0)
			{
				printf("export: `%s': not a valid identifier\n", current_c[1]);
				return ;
			}
			i++;
		}
		equal_sign = ft_strchr(current_c[1], '=');
		if (equal_sign == NULL)
			return ;
		key = current_c[1];
		value = ++equal_sign;
		add_to_env(key, value, env);
	}
}
