#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int palindrom(char *s1) {
    // 1. Finn lengden pÃ¥ strengen s1 med strlen()
    int lengde = strlen(s1);

    // 2. Bruk malloc() til Ã¥ opprette s2, sett av plass til NULL-tegnet
    char *s2 = (char *) malloc((lengde + 1) * sizeof(char));
    if (s2 == NULL) {
        return 0; // FeilhÃ¥ndtering dersom minneallokeringen feiler
    }

    // 3. KopiÃ©r alle tegnene i s1 over i s2, i omvendt rekkefÃ¸lge
    for (int i = 0; i < lengde; i++) {
        s2[i] = s1[lengde - 1 - i];
    }
    s2[lengde] = '\0'; // Legg inn NULL-tegnet sist i strengen

    // 4. Bruk strcmp() til Ã¥ finne ut om s1 er et palindrom
    // strcmp returnerer 0 hvis strengene er identiske
    int resultat = (strcmp(s1, s2) == 0);

    // FrigjÃ¸r det dynamisk allokerte minnet fÃ¸r retur
    free(s2);

    // Returner 1 (true) hvis det er et palindrom, ellers 0 (false)
    return resultat;
}

int main() {
    char s1[] = "agga";

    if (palindrom(s1)) {
        printf("Strengen \"%s\" er et palindrom.\n", s1);
    } else {
        printf("Strengen \"%s\" er IKKE et palindrom.\n", s1);
    }

    return 0;
}