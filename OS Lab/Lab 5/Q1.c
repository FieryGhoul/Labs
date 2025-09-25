#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) { // child
        printf("Child: PID=%d\n", getpid());
        sleep(2); // simulate work
        printf("Child done.\n");
        exit(0);
    }
    else { // parent
        printf("Parent waiting for child (PID=%d)...\n", pid);
        wait(&status);
        printf("Parent: Child exited with status=%d\n", WEXITSTATUS(status));
    }
    return 0;
}
