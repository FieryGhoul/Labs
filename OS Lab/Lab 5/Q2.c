#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) { // child
        printf("Child: Replacing myself with ./prog1\n");
        execl("./prog1", "prog1", NULL);
        perror("execl failed");
        exit(1);
    }
    else { // parent
        printf("Parent: PID=%d, waiting for child...\n", getpid());
        wait(NULL);
    }
    return 0;
}
