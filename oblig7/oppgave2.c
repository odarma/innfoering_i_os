#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

// Signalhandler for forelderprosessen
void sig_handler(int sig) {
    printf("Slutt Ã¥ mase, din lille satan.\n");
}

int main() {
    pid_t child = fork();

    if (child < 0) {
        perror("Fork feilet");
        exit(1);
    }

    if (child == 0) {
        // --- BARNEPROSESS ---
        char input[100];

        while (1) {
            printf("Skriv inn noe (eller 'quit' for Ã¥ avslutte): ");
            if (scanf("%99s", input) != 1) {
                break;
            }

            // Sjekk om brukeren skrev "quit"
            if (strcmp(input, "quit") == 0) {
                break;
            }

            // Send SIGUSR1 til forelderprosessen
            kill(getppid(), SIGUSR1);

            // Sove
            usleep(200000);
        }

        // Avslutt barneprosessen
        exit(0);

    } else {
        // --- FORELDERPROSESS ---
        // Registrer signalhandler for SIGUSR1
        signal(SIGUSR1, sig_handler);

        // Vent pÃ¥ at barneprosessen skal avslutte
        int status;
        wait(&status);
    }
}