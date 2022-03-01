#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main (int argc, char** argv){
    int buffer_size;

    if (argc > 1){
        buffer_size = atoi (argv[1]);
    } else{
        buffer_size = 10;
    }

    int fd_read = open("tap_file",O_RDONLY);
    if (fd_read < 0){
        //printf ("open error: %d -- %s\n", errno, stderr(erno));
        perror("open error");
        return 1;
    }

    int fd_write = open ("tap_file_copy", O_CREAT | O_WRONLY | O_TRUNC, 0600);

    // tem a ver com o tipo, usamos o ssize_t pq o dominio vai até -128 e assim
    ssize_t read_bytes = 0;
    ssize_t written_bytes = 0;

    //char buffer[buffer_size];
    char* buffer = malloc(sizeof(char)*buffer_size);

    //read_bytes = read ( fd_read, buffer, buffer_size);
    //written_bytes = write (1, buffer, read_bytes);

    while ((read_bytes = read (fd_read, buffer, buffer_size)) > 0){
        written_bytes += write (fd_write, buffer, read_bytes);
    }

    //Close file descriptors
    close (fd_read);
    close (fd_write);

    //Free buffer
    free(buffer);
    printf("Copied bytes : %ld bytes\n", written_bytes);

    return 0;
}

//gcc file_name.c
