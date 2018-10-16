#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        printf("hello from aircraft_main\n");
        char buf[20];
        while (1) {
                read(argv[1][0], buf, 10);
                printf("buf = '%s'\n", buf);
        }
        return 0;
}
