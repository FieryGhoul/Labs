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
        printf("Child (PID=%d) exiting...\n", getpid());
        exit(0);  // becomes zombie until parent exits
    }
    else { // parent
        printf("Parent (PID=%d) sleeping, Child PID=%d\n", getpid(), pid);
        sleep(30);  // during this time, child is zombie
        printf("Parent exiting now.\n");
    }
    return 0;
}
