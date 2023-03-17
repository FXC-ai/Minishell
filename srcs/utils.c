#include "../includes/header.h"

char *extract_command_name(const char *full_path)
{
	//F_OK = LE FICHIER EXITSTE, X_OK LE FICHIER EST EXECUTABLE
	if (full_path == NULL || access(full_path, F_OK | X_OK) != 0)
	{
		return NULL;
	}
	const char *last_slash = ft_strrchr(full_path, '/');
	if (last_slash == NULL)
	{
		return strdup(full_path);
	} 
	else
	{
		return strdup(last_slash + 1);
	}
	//FAUDRA FREE LE RESULT
}
