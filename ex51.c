// 208539080 Maria Dach

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <stdbool.h>


const char ERROR_MSG[] = "Error in system call";
const int ERROR_MSG_SIZE = 20;

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

int main() {
    int fd[2];
    bool isContinue = true;
    int res;
    printf("hello");
    if (pipe(fd) < 0) {
        write(2, ERROR_MSG, ERROR_MSG_SIZE);
    }
    pid_t pid = fork();
    if (pid < 0) {
        write(2, ERROR_MSG, ERROR_MSG_SIZE);
    } else {
        if (pid > 0) {
            // father
            while (isContinue) {
                printf("father is connected");
                char c = getch();
                if (c == 'q') {
                    printf("quitting");
                    isContinue = false;
                }
                printf("writting to pipe");
                res = write(fd[1], &c, 1);
                if (res < 1) {
                    write(2, ERROR_MSG, ERROR_MSG_SIZE);
                }
                printf("sending a signal");
                res = kill(pid, SIGUSR2);
                if (res) {
                    write(2, ERROR_MSG, ERROR_MSG_SIZE);
                }
            }

        } else {
            //son
            printf("son");
            char const arg[] = {NULL};
            dup2(fd[0], 0);
            execl("draw.out", arg);
        }
    }
    return 0;
}