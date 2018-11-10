#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
        printf("argc = %d\n", argc);
        int i;
        printf("args received:\n");
        for (i = 0; i < argc; i++) {
                printf("%d: %s\n", i, argv[i]);
        }
        if (argc < 2) {
                printf("usage: %s port\n", argv[0]);
                return -1;
        }

        char *server_args[] = { "server", argv[1], NULL };
        char *client_args[] = { "client", "localhost", argv[1], NULL };

        int status;
        pid_t s, c;
        printf("%s forking server\n", argv[0]);
        s = fork();
        if (s < 0) {
                perror("fork");
        } else if (s == 0) {
                execv("server", server_args);
        }
        printf("%s server forked ok, proceeding to fork client\n", argv[0]);
        c = fork();
        if (c < 0) {
                perror("fork");
        } else if (c == 0) {
                execv("client", client_args);
        }

        printf("%s: all children forked successfully, beginning wait\n", argv[0]);
        int nchildren = 2;
        pid_t cpid;
        while (nchildren > 0) {
                cpid = wait(&status);
                printf("%s: child with pid %d exited with status %d\n", argv[0], cpid, status);
                nchildren--;
        }
        printf("%s: all children done, i'm exiting\n", argv[0]);

        return 0;
}
