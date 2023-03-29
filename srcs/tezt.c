	#include <fcntl.h>
    #include <unistd.h>
	
    int main ()
    {
        int fd = open("debug2.log", O_WRONLY | O_APPEND | O_CREAT);


	    close(fd);
    
    
        return 0;
    }