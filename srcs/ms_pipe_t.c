#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>


int **matrix_creator(int process_num)
{
    int len;
	int *ptr;
    int **arr;
    int i;

	len = sizeof(int *) * process_num + sizeof(int) * 2 * process_num;
	arr = (int **)malloc(len);
	ptr = (int *)(arr + process_num);

    i = 0;
    while(i < process_num)
    {
        arr[i] = (ptr + 2 * i);
        i++;
    }

	return arr;
}



int ms_pipe(int process_num) {

    int pids[process_num];

    int **pipes = matrix_creator(process_num +1);

    int i;
    for (i = 0; i < process_num + 1; i++) 
    {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    for (i = 0; i < process_num; i++) 
    {
        pids[i] = fork();
        if (pids[i] == -1) 
        {
            printf("Error with creating process\n");
            return 2;
        }

        if (pids[i] == 0) 
        {
            // Child process
            int j;
            for (j = 0; j < process_num + 1; j++) 
            {
                if (i != j) 
                {
                    close(pipes[j][0]);
                }
                if (i + 1 != j) 
                {
                    close(pipes[j][1]);
                }
            }

            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) 
            {
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
    for (j = 0; j < process_num + 1; j++) 
    {
        if (j != process_num) {
            close(pipes[j][0]);
        }
        if (j != 0) {
            close(pipes[j][1]);
        }
    }

    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1) 
    {
        printf("Error at writing\n");
        return 4;
    }

    if (read(pipes[process_num][0], &y, sizeof(int)) == -1) 
    {
        printf("Error at reading\n");
        return 3;
    }

    printf("The final result is %d\n", y);

    close(pipes[0][1]);
    close(pipes[process_num][0]);

    for (i = 0; i < process_num; i++) 
    {
        wait(NULL);
    }
    return 0;
}


int main()
{
    ms_pipe(5);


    return 0;
}