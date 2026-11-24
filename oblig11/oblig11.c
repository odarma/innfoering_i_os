#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

#define M 100 // Maks. antall ulike typer ressurser
#define N 100 // Maks. antall prosesser
int m;        // Antall ulike typer ressurser
int n;        // Antall prosesser
int E[M];     // Exists: Totalt antall av hver type ressurs
int A[M];     // Available: Antall tilgjengelige ressursforekomster
int C[N][M];  // Current: Antall ressurser hver prosess holder
int R[N][M];  // Request: Antall ressurser hver prosess trenger
int Work[M];

// read_file(): Leser prosess- og ressursdata fra fil. Alle data mÃ¥
// vÃ¦re ikke-negative heltall.
//
void read_file(char *filename)
{
   int i, j;
   FILE *p_file;

   // Ã…pner fil og sjekker for feil i Ã¥pning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   {
      printf("Feil ved Ã¥pning av filen \"%s\"\n", filename);
      exit(-1);
   }

   // Leser antall prosesser og ressurstyper
   fscanf(p_file, "%d %d", &m, &n);

   // Leser totalt antall ressurser av hver type
   for (i = 0; i < m; i++)
     fscanf(p_file, "%d", &E[i]);

   // Leser antall ressurser av hver type som hver prosess holder
   for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
         fscanf(p_file, "%d", &C[i][j]);

   // Leser antall ressurser av hver type som hver prosess trenger
   for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
	fscanf(p_file, "%d", &R[i][j]);

   // Beregner antall tilgjengelige ressurser av hver type
   for (i = 0; i < m; i++)
   {
      A[i] = E[i];
      for (j = 0; j < n; j++)
         A[i] -= C[j][i];
   }
}


// safe(): KjÃ¸rer Bankers for Ã¥ sjekke om systemet er i safe tilstand
int safe()
{
  int i, j, done = FALSE;
  int Mark[N], n_marked = 0;
  int Work[M];

  // Initialiser merkearray
  for (i = 0; i < n; i++)
    Mark[i] = FALSE;

  // Kopier tilgjengelige ressurser til arbeidstabellen
  for (j = 0; j < m; j++)
    Work[j] = A[j];

  while (!done)
  {
    int found = FALSE;

    for (i = 0; i < n; i++)
    {
      if (!Mark[i])
      {
        // Sjekk om prosessen kan fÃ¥ det den trenger for ALLE ressurstyper
        int can_run = TRUE;
        for (j = 0; j < m; j++)
        {
          if (R[i][j] > Work[j])
          {
            can_run = FALSE;
            break;
          }
        }

        // Hvis prosessen kan kjÃ¸re
        if (can_run)
        {
          Mark[i] = TRUE;
          n_marked++;

          // Frigir ressursene prosessen holdt tilbake til Work
          for (j = 0; j < m; j++)
          {
            Work[j] += C[i][j];
          }

          // Skriver ut status i riktig format
          printf("p%d can run   A = [", i + 1);
          for (j = 0; j < m; j++)
          {
            printf(" %d", Work[j]);
          }
          printf(" ]\n");

          found = TRUE;
          break; // Starter while-lÃ¸kken pÃ¥ nytt for Ã¥ finne neste prosess
        }
      }
    }

    // Hvis vi gikk gjennom alle uten Ã¥ finne noen som kan kjÃ¸re -> Unsafe
    if (!found)
    {
      printf("No more processes can run\n");
      return FALSE;
    }

    done = (n_marked == n);
  }

  return TRUE; // Safe
}


// main(): Leser filnavn med prosess- og ressursdata fra fil og kjÃ¸rer
// Bankers algoritme
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn data fra fil
   read_file(filename);

   // Simulerer Bankers
   if (safe())
     printf("Safe\n");
   else
     printf("Unsafe\n");
}
