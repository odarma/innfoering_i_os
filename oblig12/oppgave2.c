#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main()
{
    char file_name1[256];
    char file_name2[256];
    struct stat S1;
    struct stat S2;

    printf("Please input two valid file names: ");
    scanf("%s %s", file_name1, file_name2);

    // Henter metadata med stat()
    if (stat(file_name1, &S1) < 0 || stat(file_name2, &S2) < 0) {
        perror("Feil ved kall til stat");
        return 1;
    }

    // Skriver ut informasjon for fil 1 og fil 2
    printf("%s -> I-node:%ld   Links:%hu   Size:%lld\n", file_name1, (long)S1.st_ino, S1.st_nlink, (long long)S1.st_size);
    printf("%s -> I-node:%ld   Links:%hu   Size:%lld\n\n", file_name2, (long)S2.st_ino, S2.st_nlink, (long long)S2.st_size);

    // Sjekker om de peker til samme i-node
    if (S1.st_ino == S2.st_ino) {
        printf("The two files are identical\n");
    } else {
        printf("The two files are not identical\n");
    }

    return 0;
}