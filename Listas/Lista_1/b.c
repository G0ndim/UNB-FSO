#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t sinalRecebido = 0; 
pid_t pidZumbi = -1; 

void tratadorSinal(int signo) {
    sinalRecebido = 1;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = tratadorSinal; 
    sa.sa_flags = SA_RESTART;     
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    int passos = 0;

    while (passos < 3) {
        while (!sinalRecebido) {
            pause();
        }
        sinalRecebido = 0; 

        if (passos == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                exit(0);
            } else {
                pidZumbi = pid;
            }
        } else if (passos == 1) {
            if (pidZumbi > 0) {
                waitpid(pidZumbi, NULL, 0); 
                pidZumbi = -1;
            }
        } else if (passos == 2) {
            exit(0);
        }

        passos++;
    }

    return 0;
}
