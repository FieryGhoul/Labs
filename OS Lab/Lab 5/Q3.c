#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) { // child
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    }
    else { // parent
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);
    }
    return 0;
}
