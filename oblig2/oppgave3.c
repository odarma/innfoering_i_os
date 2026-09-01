#include <stdio.h>
#include <stdlib.h>

void skriv_til_fil(long f[], int n){
    FILE* fil = fopen("fibonacci.txt", "w");
    if (fil == NULL) {
        printf("Feil ved Ã¥pning av fil for skriving.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fil, "%ld\n", f[i]);
    }

    fclose(fil);
}

void les_fra_fil(){
    FILE* fil = fopen("fibonacci.txt", "r");
    if (fil == NULL) {
        printf("Feil ved lesing av fil\n");
        exit(1);
    }

    long tall;
    printf("\nLeser fra fil:\n");
    while (fscanf(fil, "%ld", &tall) == 1) {
        printf("%ld\n", tall);
    }

    fclose(fil);
}

void fib(int n) {
    if (n <= 0) return;

    long f[n];
    f[0] = 0;
    if (n > 1) {
        f[1] = 1;
    }

    for (int i = 2; i < n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    for (int i = 0; i < n; i++) {
        printf("%ld\n", f[i]);
    }

    skriv_til_fil(f, n);
}

int main() {
    int n;

    printf("Skriv inn tallet som programmet skal beregne Fibonaccitallene opptil: ");
    scanf("%d", &n);
    fib(n);
    printf("\n");
    les_fra_fil();
}