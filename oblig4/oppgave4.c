#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    int status = 0;
    pid_t child = fork();

    if (child == 0) {
        char *argv[3];
        argv[0] = "ping";
        argv[1] = "vg.no";
        argv[2] = NULL;

        printf("Barneprosessen med PID %d skal pinge vg.no\n", getpid());
        execvp(argv[0], argv);
    } else {
        printf("Forelderprosess med PID %d\n", getpid());
        sleep(5);

        kill(child, SIGINT);

	// SIGINT: Tilsvarende å trykke Ctrl+C.
	// ping rekker å fange signalet og skrive ut oppsummeringsstatistikk om pakker får den avslutter pent.

	// SIGKILL: Tvinger prosessen til å avslutte umiddelbart. ping rekker ikke å skrive ut noe statistikk.
    }
}