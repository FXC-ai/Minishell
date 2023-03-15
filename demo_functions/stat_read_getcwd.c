
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/stat.h>

int	main(void)
{
	char    *line;
	char    cwd[1024];
	struct stat t;
	
	getcwd(cwd, 1024);
	printf("%s\n", cwd);

	while(42)
	{
		line = readline("test ");
		add_history(line);
		printf("%s\n", line);
		stat("minishell", &t);
		printf("Taille du fichier : %lld\n", t.st_size);
		printf("Horodatage de dernière modification : %ld\n", t.st_mtime);
		printf("Permissions : %o\n", t.st_mode & 0777);
	}

	return (0);
}