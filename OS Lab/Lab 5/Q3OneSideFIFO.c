/* fifo_writer_only.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"

int main(void) {
    int fd;
    const char *msg = "single side writer message\n";

    if (access(FIFO_NAME, F_OK) == -1) {
        if (mkfifo(FIFO_NAME, 0666) == -1) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }

    write(fd, msg, strlen(msg));
    close(fd);
    return 0;
}
