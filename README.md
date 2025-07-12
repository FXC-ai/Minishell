# Minishell

[GitHub - widium/Minishell: create a minimalist shell with the basic built-in Function of bash](https://github.com/widium/Minishell)

# Liste des fonctions

//MAIN.C

void    sig_init(void);

void disable_ctrl_chars();

int check_entry(char *line);

void    wait_for_input(char *env[]);

//REDIRECTION.C

void    execute_command(char **parsed_args, int in_fd, int out_fd, char *env[]);

void    execute_command_2(char **parsed_args, int in_fd, int out_fd, char *env[]);

int process_delimiter(char *del);

int     process_redirection(char *str, char *env[], int mode);

//SIGNAL.C

void    signal_handler();

//PARSE_ARGS.C

//void    parsing(char **args, char *env[]);

//LEXER.C

int is_space(char c);

char    **lexer(char *str, char *env[]);

char    **ft_split_lexer(char const *str, char c);

int     count_chr(const char *str, char c);

void parse_dollar(char **tab_cmds, char *env[]);

char *find_env_variable (char *var_name, char *env[]);

char *ft_strndup(char *str, size_t n);

void normalize_with_space(char **str);

//FT_LEXER_NO_QUOTE.C

char    **ft_lexer_no_quote(char const *str, char c);

//UTILS.C

void    print_tab(char **tab);

int get_max_length(char *str1, char *str2);

char *extract_command_name(const char *full_path);

void    ft_free_tabs(char **tab, int h);

int size_tab(char **tab);

char    **create_tab_paths(char *env[]);

char    *create_path_cmd(char *path, char *cmd);

char    *cmd_exists(char *cmd, char *env[]);

char    *normalize_cmd(char* str, char *env[]);

int     is_builtins(char *str);

void    freemalloc(char **result, int j);

//MS_PIPE.C

void execute_last_cmd(int pipe_fd[2], char **tab_cmds, int nbr_cmds, char *env[]);

void execute_first_cmd(int pipe_fd[2], char **tab_cmds, char *env[]);

void redirection (char *input_cmd, int previous_pipe[2], int next_pipe[2], char *env[]);

void execution (char *input_cmd, char *env[]);

void ms_pipe2(char **tab_cmds, char *env[]);

//BUILTINS

void    echo_process(char **cmd);

void    cd_process(char **current_command, char *env[]);

void    pwd_process();

int     unset_process(char **parsed_args, char *env[]);

void    env_process(char **parsed_args, char *env[]);

void    export_process(char **current_command, char *env[]);

void add_to_env(char *ligne, char *value, char *env[]);

void    exit_process();

int     unset_process_str(char *key, char *env[]);

# Sources

[GitHub - Swoorup/mysh: A basic unix shell interpreter in c programming language using recursive descent parser.](https://github.com/Swoorup/mysh)

Projet shell

[](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

Tutoriel pour créer un shell

[GitHub - DimitriDaSilva/42_minishell: Writing a shell in C - 42 Lisboa Project](https://github.com/DimitriDaSilva/42_minishell)

# Testeurs

[minishell-test](https://pypi.org/project/minishell-test/)

[GitHub - cacharle/minishell_test: Test for 42 school's minishell project](https://github.com/cacharle/minishell_test)

ps aux : permet d afficher les processus en cours sur la machine

sigaction()

La fonction sigaction en C est utilisée pour définir le comportement d'un processus lorsqu'il reçoit un signal du système d'exploitation. Voici un exemple d'utilisation de la fonction sigaction pour gérer le signal SIGINT (signal d'interruption) :

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Received signal %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    while (1) {
        printf("Waiting for signal...\n");
        sleep(1);
    }
    return 0;
}
```

Dans cet exemple, nous avons défini une fonction de gestionnaire de signal appelée "handler" qui affiche simplement le numéro de signal reçu. Nous avons ensuite créé une structure sigaction, défini son champ sa_handler pour qu'il pointe vers notre fonction handler, et configuré le reste des champs à des valeurs par défaut. Nous avons ensuite utilisé la fonction sigaction pour lier notre gestionnaire de signal à SIGINT. Enfin, nous avons créé une boucle infinie qui attend des signaux.

Lorsque nous exécutons ce programme, il entre dans la boucle infinie et affiche "Waiting for signal..." toutes les secondes. Si nous appuyons sur Ctrl+C pour envoyer le signal SIGINT au processus, le gestionnaire de signal handler est appelé et affiche "Received signal 2" (2 étant le numéro de signal pour SIGINT). Le programme continue ensuite à boucler et à attendre des signaux.

La structure sigaction :

```c
struct  sigaction 
{
	union __sigaction_u __sigaction_u;  /* signal handler **/
	sigset_t sa_mask;                   /** signal mask to apply **/
	int     sa_flags;*                   
};
```

L’union sigaction :

```c
union __sigaction_u 
{
	void    (*__sa_handler)(int);
	void    (*__sa_sigaction)(int, siginfo_t *, void *);
};
```

Difference entre ‘’ et “”

Entre ‘’ : aucun metacaratere ne doit etre interpreté

Entre “” : le $ doit être interprété entant que metacaractere

La fonction export à coder

La fonction export sans aucun argument affiche toutes les variables qui ont été exportées depuis le shell qui a lancé Minishell.

[Exportation de variables de shell (commande de shell export)](https://www.ibm.com/docs/fr/aix/7.3?topic=customization-exporting-shell-variables-export-shell-command)

La fonction export permet de transformer une variable locale en variable d’environnement.

getcwd()

La fonction getcwd() est utilisée en C pour obtenir le chemin du répertoire de travail actuel. Voici un exemple simple d'utilisation de cette fonction :

```c
#include <stdio.h>#include <unistd.h>int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Le répertoire de travail actuel est : %s\n", cwd);
    } else {
        perror("getcwd() a échoué");
        return 1;
    }
    return 0;
}
```

Dans cet exemple, nous incluons les en-têtes standard <stdio.h> et <unistd.h>. La fonction getcwd() est appelée avec deux arguments : un pointeur vers une chaine de caractères où le chemin du répertoire de travail sera stocké, et la taille de cette chaine de caractère.

Si getcwd() réussit, elle renvoie un pointeur vers le tampon contenant le chemin du répertoire de travail actuel. Nous affichons ensuite ce chemin en utilisant la fonction printf(). Si getcwd() échoue, elle renvoie NULL et nous appelons la fonction perror() pour afficher un message d'erreur.

chdir()

chdir sera utile pour coder la fonction cd.

La fonction chdir() en C est utilisée pour changer le répertoire de travail actuel. Voici un exemple simple d'utilisation de cette fonction :

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    char *new_directory = "/chemin/vers/nouveau/repertoire";
    if (chdir(new_directory) != 0) {
        perror("chdir() a échoué");
        return 1;
    } else {
        printf("Le répertoire de travail actuel a été changé avec succès.\n");
    }
    return 0;
}
```

Dans cet exemple, nous avons défini une chaîne de caractères contenant le chemin du nouveau répertoire dans lequel nous voulons changer. Nous appelons ensuite la fonction chdir() en passant cette chaîne de caractères comme argument.

Si chdir() réussit, elle renvoie 0 et le répertoire de travail actuel est changé pour le nouveau répertoire. Si chdir() échoue, elle renvoie -1.

Notez que le chemin du nouveau répertoire doit être valide et accessible pour que chdir() réussisse. Si le chemin est incorrect ou si l'utilisateur n'a pas les permissions nécessaires pour accéder au répertoire, chdir() renverra une erreur.

stat()

La fonction stat() en C est utilisée pour obtenir des informations sur un fichier. Voici un exemple simple d'utilisation de cette fonction :

```c
#include <stdio.h>
#include <sys/stat.h>

int main() 
{
    char *filename = "demo_chdir.c";
    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) 
	{
        perror("stat() a échoué");
        return 1;
    } 
	else 
	{
        printf("Taille du fichier : %lld octets\n", file_stat.st_size);
        printf("Dernière modification : %ld", file_stat.st_mtime);
    }
    return 0;
}
```

Dans cet exemple, nous avons défini une chaîne de caractères contenant le chemin vers le fichier dont nous voulons obtenir des informations. Nous avons également déclaré une structure stat qui sera utilisée pour stocker les informations du fichier.

Nous appelons ensuite la fonction stat() en passant le chemin du fichier et un pointeur vers la structure stat. Si la fonction réussit, elle remplit la structure avec les informations du fichier.

Dans cet exemple, nous affichons la taille du fichier en utilisant la propriété st_size de la structure stat, qui contient la taille du fichier en octets. Nous affichons également la date et l'heure de la dernière modification du fichier en timestamp.

Si la fonction stat() échoue, elle renvoie -1 et nous appelons la fonction perror() pour afficher un message d'erreur.

Voici la structure utilisée par stat :

```c
struct stat { 
         dev_t    st_dev;    /* device inode resides on */
         ino_t    st_ino;    /* inode's number */
         mode_t   st_mode;   /* inode protection mode */
         nlink_t  st_nlink;  /* number of hard links to the file */
         uid_t    st_uid;    /* user-id of owner */
         gid_t    st_gid;    /* group-id of owner */
         dev_t    st_rdev;   /* device type, for special file inode */
         struct timespec st_atimespec;  /* time of last access */
         struct timespec st_mtimespec;  /* time of last data modification */
         struct timespec st_ctimespec;  /* time of last file status change */
         off_t    st_size;   /* file size, in bytes */
         quad_t   st_blocks; /* blocks allocated for file */
         u_long   st_blksize;/* optimal file sys I/O ops blocksize */
         u_long   st_flags;  /* user defined flags for file */
         u_long   st_gen;    /* file generation number */
     };
```

lstat()

Même chose que la fonction stat à la différence que si on met un chemin vers un lien symbolique, lstat renvoie les informations à propos du lien.

fstat()

Elle permet d’obtenir les informations sur un fichier ouvert à partir de son file descriptor.

unlink()

La fonction unlink() en C est utilisée pour supprimer un fichier. Voici un exemple simple d'utilisation de cette fonction :

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    char *filename = "chemin/vers/le/fichier/a/supprimer";
    if (unlink(filename) != 0) {
        perror("unlink() a échoué");
        return 1;
    } else {
        printf("Le fichier a été supprimé avec succès.\n");
    }
    return 0;
}
```

Dans cet exemple, nous avons défini une chaîne de caractères contenant le chemin vers le fichier que nous voulons supprimer. Nous appelons ensuite la fonction unlink() en passant cette chaîne de caractères comme argument.

Si unlink() réussit, elle renvoie 0 et le fichier est supprimé. Si unlink() échoue, elle renvoie -1 et nous appelons la fonction perror() pour afficher un message d'erreur.

Notez que la fonction unlink() ne peut supprimer que des fichiers réguliers, elle ne peut pas supprimer des répertoires ou des liens symboliques. De plus, si le fichier est ouvert par un autre processus ou utilisateur, la suppression échouera.

opendir()

La fonction opendir() en C est utilisée pour ouvrir un répertoire et obtenir un pointeur vers sa structure DIR. Voici un exemple simple d'utilisation de cette fonction :

```c
#include <stdio.h>
#include <dirent.h>

int main() {
    char *dirname = "chemin/vers/le/repertoire";
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dirname)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir() a échoué");
        return 1;
    }
    return 0;
}
```

Dans cet exemple, nous avons défini une chaîne de caractères contenant le chemin vers le répertoire que nous voulons ouvrir. Nous avons également déclaré un pointeur vers la structure DIR qui sera utilisée pour stocker les informations sur le répertoire, ainsi qu'un pointeur vers la structure dirent qui sera utilisé pour stocker les informations sur les entrées du répertoire.

Nous appelons ensuite la fonction opendir() en passant le chemin du répertoire comme argument. Si la fonction réussit, elle renvoie un pointeur vers la structure DIR. Nous parcourons ensuite le contenu du répertoire en appelant la fonction readdir() à plusieurs reprises. Cette fonction lit les entrées du répertoire une par une, et renvoie un pointeur vers la structure dirent correspondante. Nous affichons alors le nom de chaque entrée en utilisant la propriété d_name de la structure dirent.

Enfin, nous appelons la fonction closedir() pour fermer le répertoire. Si opendir() échoue, elle renvoie NULL et nous appelons la fonction perror() pour afficher un message d'erreur.

Notez que cette fonction ne parcourt pas les sous-répertoires, elle ne lit que les entrées directes

readir()

Voici un exemple d'utilisation de la fonction `readdir` en C pour parcourir le contenu d'un répertoire et afficher le nom de chaque fichier :

```c
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *ent;
    char *path = "."; // Chemin du répertoire à parcourir

    // Ouvre le répertoire
    dir = opendir(path);
    if (dir == NULL) 
		{
        perror("Erreur lors de l'ouverture du répertoire");
        return -1;
    }

    // Parcourt le contenu du répertoire
    while ((ent = readdir(dir)) != NULL) 
		{
        printf("%s\n", ent->d_name);
    }

    // Ferme le répertoire
    closedir(dir);
    return 0;
}

```

Ce programme ouvre le répertoire courant (représenté par le chemin `.`), parcourt son contenu en utilisant la fonction `readdir`, et affiche le nom de chaque fichier trouvé à l'écran en utilisant `printf`. Enfin, le programme ferme le répertoire avec la fonction `closedir`.

isatty()

La fonction `isatty` en C est utilisée pour déterminer si un descripteur de fichier fait référence à un terminal. Voici un exemple d'utilisation de la fonction `isatty` en C :

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    if (isatty(STDOUT_FILENO)) {
        printf("La sortie standard est reliée à un terminal\n");
    } else {
        printf("La sortie standard n'est pas reliée à un terminal\n");
    }
    return 0;
}
```

Ce programme utilise la fonction `isatty` pour déterminer si la sortie standard est reliée à un terminal. La fonction `isatty` prend un descripteur de fichier en entrée et renvoie une valeur différente de zéro si le descripteur de fichier fait référence à un terminal, et zéro sinon.

ttyname()

La fonction `tyname` en C est utilisée pour obtenir le nom du type de terminal associé à un descripteur de fichier. Voici un exemple d'utilisation de la fonction `tyname` en C :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios term;
    char *name;

    if (tcgetattr(STDIN_FILENO, &term) < 0) {
        perror("Erreur lors de l'obtention des attributs du terminal");
        return -1;
    }

    name = ttyname(STDIN_FILENO);
    if (name == NULL) {
        perror("Erreur lors de l'obtention du nom du terminal");
        return -1;
    }

    printf("Le nom du terminal associé au descripteur de fichier est : %s\n", name);

    return 0;
}
```

Ce programme utilise la fonction `tcgetattr` pour obtenir les attributs du terminal associé à l'entrée standard (`STDIN_FILENO`). Ensuite, la fonction `ttyname` est utilisée pour obtenir le nom du type de terminal associé à l'entrée standard. La fonction `ttyname` renvoie un pointeur vers une chaîne de caractères contenant le nom du type de terminal, ou `NULL` en cas d'erreur.

tcgetattr()

Ce programme utilise la fonction `tcgetattr` pour obtenir les attributs du terminal associé à l'entrée standard (`STDIN_FILENO`). La fonction `tcgetattr` remplit une structure `termios` avec les attributs actuels du terminal. Les attributs peuvent ensuite être affichés à l'écran à l'aide de la structure `termios`.

# Gestion des pipe

[Creating multiple process using fork() - GeeksforGeeks](https://www.geeksforgeeks.org/creating-multiple-process-using-fork/)

Exemple :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num_processes = 5; // nombre de processus à créer
    pid_t pid;

    // boucle pour créer les processus enfants
    for (int i = 0; i < num_processes; i++) {
        pid = fork(); // création d'un nouveau processus enfant

        if (pid < 0) { // si la création a échoué
            printf("Erreur lors de la création du processus enfant.");
            exit(1);
        } else if (pid == 0) { // si c'est le processus enfant
            printf("Je suis le processus enfant %d avec PID %d.\n", i+1, getpid());
            exit(0);
        }
    }

    // attente de la fin de tous les processus enfants
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("Tous les processus enfants sont terminés.\n");

    return 0;
}
```

Ce code utilise une boucle pour créer `num_processes` processus enfants. Chaque processus enfant affiche son numéro et son PID, puis se termine avec la fonction `exit()`. Le processus parent attend ensuite la fin de tous les processus enfants avec la fonction `wait()` avant de se terminer lui-même.

Notez que la création de processus avec `fork` peut être coûteuse en termes de ressources système. Il est donc important de s'assurer que le nombre de processus créés est raisonnable et justifié.

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int pipefd[2];
    int pipefd2[2];
    pid_t pid1, pid2;
    char buf[1024];

    if (pipe(pipefd) == -1) {   // Création du premier pipe
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd2) == -1) {   // Création du deuxième pipe
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();   // Création du premier fils
    if (pid1 == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {   // Le premier fils
        close(pipefd[1]);   // Ferme le descripteur d'écriture du premier pipe
        dup2(pipefd[0], STDIN_FILENO);   // Redirige l'entrée standard vers la lecture du premier pipe
        close(pipefd[0]);   // Ferme le descripteur de lecture du premier pipe

        close(pipefd2[0]);   // Ferme le descripteur de lecture du deuxième pipe
        dup2(pipefd2[1], STDOUT_FILENO);   // Redirige la sortie standard vers l'écriture du deuxième pipe
        close(pipefd2[1]);   // Ferme le descripteur d'écriture du deuxième pipe

        execlp("grep", "grep", "foo", NULL);   // Exécute la commande grep avec l'entrée provenant du premier pipe et la sortie vers le deuxième pipe
        exit(EXIT_FAILURE);
    }

    pid2 = fork();   // Création du deuxième fils
    if (pid2 == -1) {
        perror("fork2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {   // Le deuxième fils
        close(pipefd2[1]);   // Ferme le descripteur d'écriture du deuxième pipe
        dup2(pipefd2[0], STDIN_FILENO);   // Redirige l'entrée standard vers la lecture du deuxième pipe
        close(pipefd2[0]);   // Ferme le descripteur de lecture du deuxième pipe

        execlp("wc", "wc", "-l", NULL);   // Exécute la commande wc avec l
```

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int pipe1[2], pipe2[2];
    pid_t pid;

    if (pipe(pipe1) == -1) {
        perror("Erreur lors de la création de pipe 1");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2) == -1) {
        perror("Erreur lors de la création de pipe 2");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("Erreur lors de la création d'un nouveau processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Premier enfant
        close(pipe1[0]); // Ferme la fin de lecture de pipe1
        dup2(pipe1[1], STDOUT_FILENO); // Redirige la sortie standard vers pipe1
        close(pipe1[1]); // Ferme la fin d'écriture de pipe1

        execlp("ls", "ls", "-al", NULL); // Exécute la commande ls -al
        perror("Erreur lors de l'exécution de la commande ls"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("Erreur lors de la création d'un nouveau processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Deuxième enfant
        close(pipe1[1]); // Ferme la fin d'écriture de pipe1
        dup2(pipe1[0], STDIN_FILENO); // Redirige l'entrée standard depuis pipe1
        close(pipe1[0]); // Ferme la fin de lecture de pipe1

        close(pipe2[0]); // Ferme la fin de lecture de pipe2
        dup2(pipe2[1], STDOUT_FILENO); // Redirige la sortie standard vers pipe2
        close(pipe2[1]); // Ferme la fin d'écriture de pipe2

        execlp("grep", "grep", "test", NULL); // Exécute la commande grep test
        perror("Erreur lors de l'exécution de la commande grep"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("Erreur lors de la création d'un nouveau processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Troisième enfant
        close(pipe2[1]); // Ferme la fin d'écriture de pipe2
        dup2(pipe2[0], STDIN_FILENO); // Redirige l'entrée standard depuis pipe2
        close(pipe2[0]); // Ferme la fin de lecture de pipe2

        execlp("wc", "wc", "-l", NULL); // Exécute la commande wc -l
        perror("Erreur lors de l'exécution de la commande wc"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    // Processus parent
    close(pipe1[0]); // Ferme la fin de lecture de pipe1
    close(pipe1[1]); // Ferme la fin d'écriture de pipe1
    close(pipe2[0]); // Ferme la fin de lecture de pipe2
    close(pipe2[1]); // Ferme la fin d'éc
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_cmds = 3; // Nombre de commandes à exécuter
    char *cmds[][3] = {{"ls", "-al", NULL}, {"grep", ".txt", NULL}, {"wc", "-l", NULL}}; // Commandes à exécuter

    int pipes[num_cmds - 1][2]; // Tableau de pipes
    pid_t pids[num_cmds]; // Tableau de pids

    // Crée les pipes
    for (int i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Erreur de création des pipes");
            exit(EXIT_FAILURE);
        }
    }

    // Exécute les commandes
    for (int i = 0; i < num_cmds; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Erreur de création du processus fils");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            // Processus fils
            if (i == 0) {
                // Premier processus : redirige la sortie standard vers le côté écriture de la première pipe
                close(pipes[i][0]);
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);
            } else if (i == num_cmds - 1) {
                // Dernier processus : redirige l'entrée standard vers le côté lecture de la dernière pipe
                close(pipes[i - 1][1]);
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
            } else {
                // Processus intermédiaire : redirige l'entrée standard vers le côté lecture de la pipe précédente
                // et la sortie standard vers le côté écriture de la pipe suivante
                close(pipes[i - 1][1]);
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);

                close(pipes[i][0]);
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);
            }

            execvp(cmds[i][0], cmds[i]);
            perror("Erreur d'exécution de la commande");
            exit(EXIT_FAILURE);
        }
    }

    // Attends la fin de tous les processus fils
    for (int i = 0; i < num_cmds; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}
```

[](https://code-vault.net/lesson/v5cml4fg0w:1610639843712)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

int main(int argc, char* argv[]) {

    int pids[PROCESS_NUM];

    int pipes[PROCESS_NUM + 1][2];

    int i;
    for (i = 0; i < PROCESS_NUM + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    for (i = 0; i < PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        if (pids[i] == 0) {
            // Child process
            int j;
            for (j = 0; j < PROCESS_NUM + 1; j++) {
                if (i != j) {
                    close(pipes[j][0]);
                }
                if (i + 1 != j) {
                    close(pipes[j][1]);
                }
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) {
                printf("Error at reading\n");
                return 3;
            }
            printf("(%d) Got %d\n", i, x);
            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) {
                printf("Error at writing\n");
                return 4;
            }
            printf("(%d) Sent %d\n", i, x);
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            return 0;
        }
    }

    // Main process
    int j;
    for (j = 0; j < PROCESS_NUM + 1; j++) {
        if (j != PROCESS_NUM) {
            close(pipes[j][0]);
        }
        if (j != 0) {
            close(pipes[j][1]);
        }
    }
    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1) {
        printf("Error at writing\n");
        return 4;
    }
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) {
        printf("Error at reading\n");
        return 3;
    }
    printf("The final result is %d\n", y);
    close(pipes[0][1]);
    close(pipes[PROCESS_NUM][0]);

    for (i = 0; i < PROCESS_NUM; i++) {
        wait(NULL);
    }
    return 0;
}
```

Logique du multipipe de Minishell

3 cas :

|  | Redirection | Pipe |
| --- | --- | --- |
| cmd 1 | Oui | vide |
| cmd 2 | Non | data |
| cmd 3 |  |  |
| cmd 4 |  |  |
| cmd 5 |  |  |

# Coin des notes

ps -l permet d’afficher tous les processus ratachés au terminal avec leur pid.

[https://forums.commentcamarche.net/forum/affich-6347498-allocation-dynamique-d-une-matrice-en-c](https://forums.commentcamarche.net/forum/affich-6347498-allocation-dynamique-d-une-matrice-en-c)

M=(int**) malloc (sizeof(int*)*l);

[How to dynamically allocate a 2D array in C? - GeeksforGeeks](https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/)

# Evaluation

## Partie obligatoire

### Compilation

- [ ]  Utilisez "make -n" to pour vous assurer que le projet compile avec "-Wall -Wextra -Werror".
- [ ]  Le minishell compile sans aucune erreur.
- [ ]  Le Makefile ne doit pas re-link. Si ce n'est pas le cas, cochez le flag.

### Commande simple et variables globales

- [ ]  Exécutez une commande simple avec un PATH absolu tel que /bin/ls ou n'importe quelle autre commande sans option.
- [ ]  Combien de variables globales y a-t-il ? Pourquoi ? Demandez à la personne évaluée de vous donner un exemple concret pour démontrer que leur usage est obligatoire et cohérent.
- [ ]  Testez une commande vide.
- [ ]  Testez seulement des espaces et des tabs.

### Arguments

- [ ]  Exécutez une commande simple avec un PATH absolu tel que /bin/ls ou n'importe quelle autre commande,
- [ ]  Même chose avec option mais sans '' (single quotes) ni "" (double quotes).
- [ ]  Répétez ce test plusieurs fois avec différentes commandes et différents arguments.

### echo

- [ ]  Lancez la commande echo avec et sans argument ou options, ou avec l'option -n.
- [ ]  Répétez ce test plusieurs fois avec différents arguments.

### exit

- [ ]  Lancez la commande exit avec et sans arguments.
- [ ]  Répétez ce test plusieurs fois avec différents arguments.

### Valeur de retour d'un processus

- [ ]  Exécutez des commandes simple avec un chemin absolu tel que /bin/ls ou n'importe quelle autre commande avec des arguments mais sans '' (single quotes) ni "" (double quotes), puis lancez "echo $?". Vérifiez la valeur affichée. Vous pouvez le refaire dans bash et comparer.
- [ ]  Répétez ce test plusieurs fois avec différentes commandes et différents arguments.
- [ ]  Utilisez des commandes qui ne fonctionnent pas telles que '/bin/ls fichiernul'.
- [ ]  Essayez des expressions telles que $? + $?

### Signaux

- [ ]  ctrl-C dans un prompt vide devrait afficher une nouvelle ligne avec un nouveau prompt.
- [ ]  ctrl-\ dans un prompt vide ne devrait rien faire.
- [ ]  ctrl-D dans un prompt vide devrait quitter minishell. Ensuite, relancez-le.
- [ ]  ctrl-C dans un prompt après avoir écrit des choses devrait afficher une nouvelle ligne avec un nouveau prompt.
- [ ]  Également, le buffer devrait être vide. Appuyez sur "Entrée" afin de vous assurer que la ligne précédente a été exécutée.
- [ ]  ctrl-D dans un prompt après avoir écrit des choses ne devrait rien faire.
- [ ]  ctrl-\ dans un prompt après avoir écrit des choses ne devrait rien faire.
- [ ]  Essayez ctrl-C après avoir lancé une commande bloquante, comme cat ou grep sans argument.
- [ ]  Essayez ctrl-\ après avoir lancé une commande bloquante, comme cat ou grep sans argument.
- [ ]  Essayez ctrl-D après avoir lancé une commande bloquante, comme cat ou grep sans argument.
- [ ]  Répétez plusieurs fois en utilisant des commandes différentes.

### Double Quotes

- [ ]  Exécutez une commande simple avec des arguments, mais cette fois utilisez des guillemets (rajoutez des ';' et des espaces entre les guillemets).
- [ ]  Essayez une commande comme : echo "cat lol.c | cat > lol.c"
- [ ]  N'essayez pas $.

### Single Quotes

- [ ]  Exécutez des commandes avec des single quotes dans les arguments.
- [ ]  Essayez des arguments vides.
- [ ]  Faites des tests avec des variables d'environnement, des espaces, des pipes, des redirections entre les guillemets.
- [ ]  echo '$USER' doit afficher "$USER". Rien ne devrait être interprété.

### env

- [ ]  Vérifiez qu'env vous affiche bien les variables d'environnement.

### export

- [ ]  Exportez des variables d'environnement, dont certaines pour remplacer les anciennes. Vérifiez le résultat avec env.

### unset

- [ ]  Exportez des variables d'environnement, dont certaines pour remplacer les anciennes.
- [ ]  Utilisez unset pour en retirer. Vérifiez le résultat avec env.

### cd

- [ ]  Utilisez la commande cd pour vous déplacer dans l'arborescence et utilisez /bin/ls pour vérifier que vous êtes dans le bon répertoire.
- [ ]  Répétez ce test plusieurs fois avec des cd qui fonctionnent et qui ne fonctionnent pas.
- [ ]  Essayez aussi '.' et '..' en arguments.

### pwd

- [ ]  Utilisez la commande pwd, avec et sans argument.
- [ ]  Répétez ce test plusieurs fois dans différents répertoires.
- [ ]  Essayez '.' et '..' en arguments.

### Chemin relatif

- [ ]  Exécutez des commandes en utilisant un chemin relatif.
- [ ]  Répétez ce test plusieurs fois dans d'autres dossier avec un chemin relatif complexe (beaucoup de ..).

### PATH d'environnement

- [ ]  Exécutez des commandes mais sans PATH (ls, wc, awk, etc...).
- [ ]  Retirez le $PATH et vérifiez si les commandes ne fonctionnent plus.
- [ ]  Mettez plusieurs répertoires à PATH (directory1:directory2) et vérifiez qu'ils sont bien évalués de gauche à droite.

### Redirection

- [ ]  Exécutez des commandes avec les redirections < et/ou >
- [ ]  Répétez ce test plusieurs fois avec différentes commandes et différents arguments et, quelques fois, utilisez >> au lieu de >.
- [ ]  Vérifiez si plusieurs instances de la même redirection échouent.
- [ ]  Testez les redirections avec << (cela ne doit pas forcément mettre à jour l'historique).

### Pipes

- [ ]  Exécutez des commandes avec des pipes telles que 'cat file | grep bla | more'
- [ ]  Répétez plusieurs fois avec différentes commandes et différents arguments.
- [ ]  Essayez des commandes qui échouent telles que 'ls fichiernul | grep bla | more'
- [ ]  Mixez les pipes et les redirections.

### Soyons fous ! Et l'historique

- [ ]  Entrez une commande, puis ctrl-C, et appuyez sur "Entrée". Le buffer devrait être vide et il ne devrait plus rien avoir à exécuter.
- [ ]  Peut-on naviguer dans l'historique avec Haut et Bas (profitez-en pour relancer des commandes) ?
- [ ]  Exécutez des commandes qui ne fonctionnent pas telles que 'dskdskdksd' et vérifiez que tout fonctionne comme prévu.
- [ ]  'cat | cat | ls' doit fonctionner.
- [ ]  Essayez des commandes vraiment, vraiment longues avec des tonnes d'arguments.

### Variables d'environnement

- [ ]  Exécutez echo avec des variables d'environnement ($variable) en argument.
- [ ]  Assurez-vous que $ est interprété correctement.
- [ ]  Vérifiez que les guillemets autour des $variables fonctionnent correctement (comme dans bash).
- [ ]  Si USER n'existe pas, définissez-la. Ainsi, echo "$USER" devrait afficher la valeur de $USER.

# Schémas de l’évolution du projet pendant le développement

![minishell_draw(2).png](Minishell%2002b146c5cf414b3385d5440234325476/minishell_draw(2).png)

![minishell_draw(3).png](Minishell%2002b146c5cf414b3385d5440234325476/minishell_draw(3).png)
