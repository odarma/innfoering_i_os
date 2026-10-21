#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en prosess
struct process
{
   int id;      // Prosess-ID
   int arrive;  // Tidspunkt da prosessen ble satt inn i kÃ¸
   int cpu;     // Total CPU-tid som prosessen krever
   int start;   // Tidspunkt da prosessen startet Ã¥ kjÃ¸re
   int end;     // Tidspunkt da prosessen er ferdig
};

// Globale variabler
int T = 0;         // Systemtid, starter simulering ved tid lik 0
int N;             // Antall prosesser
struct process *P; // Peker til array med prosessene

// read_file(): Leser data for N prosesser fra fil. Prosessene skal
// ligge sortert pÃ¥ ankomsttid. Alle data mÃ¥ vÃ¦re ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id arrive CPU
//    id arrive CPU
//    id arrive CPU
//    ...
//
void read_file(char *filename)
{
   int i, last_arrive = 0;
   FILE *p_file;

   // Ã…pner fil og sjekker for feil i Ã¥pning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   {
      printf("Feil ved Ã¥pning av filen \"%s\"\n", filename);
      exit(-1);
   }

   // Leser antall prosesser
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle prosessene
   P = (struct process *) malloc(N * sizeof(struct process));

   // Leser inn en og en prosess. Prosessene skal ligge sortert pÃ¥
   // ankomsttid i filen, hvis ikke gis en feilmelding.
   for (i = 0; i < N; i++)
   {
      fscanf(p_file, "%d %d %d", &P[i].id, &P[i].arrive, &P[i].cpu);
      P[i].start = P[i].end = 0;

      if (P[i].arrive < last_arrive)
      {
	 printf("Feil i ankomsttider, prosess %d\n", P[i].id);
         exit(-1);
      }
      last_arrive = P[i].arrive;
   }
   fclose(p_file);
}

// simulate(): Simulering av batch scheduling. "KjÃ¸rer" til alle
// prosessene er ferdige.
//
void simulate()
{
  // Skal programmeres ferdig i oppgavene
	int i;
	float average_turnaround = 0;
	float average_ventetid = 0;

	printf("P	arrive	cpu	start	end\n");
	for (i=0; i<N; i++){
		if (T < P[i].arrive){
			T = P[i].arrive;
		}

		P[i].start = T;
		P[i].end = P[i].start + P[i].cpu;

		T = P[i].end;

		printf("%d	%d	%d	%d	%d\n", P[i].id, P[i].arrive, P[i].cpu, P[i].start, P[i].end);

		int turnaround = P[i].end - P[i].arrive;
    		int ventetid = turnaround - P[i].cpu;

    		average_turnaround += turnaround;
    		average_ventetid += ventetid;
	}
	printf("average turnaround: %.2f\n average wait-time: %.2f\n", average_turnaround/((float) N), average_ventetid/((float) N));
}


// main(): Leser filnavn med prosessdata, leser fil og kjÃ¸rer scheduling
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer batch-scheduling
   simulate();
}
