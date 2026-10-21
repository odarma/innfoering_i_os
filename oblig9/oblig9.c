#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en page frame
struct page_frame
{
   int id;   // Page-ID/-number
   int load; // Tidspunkt da pagen ble lagt inn i RAM
   int last; // Tidspunkt da pagen siste ble referert til
   int R;    // Referenced bit
   int M;    // Modified bit
};

// Globale variabler
int T = 300;           // Systemtid, settes til passende verdi
int N;                 // Antall prosesser
struct page_frame *PF; // Peker til array med page frames

// read_file(): Leser data for N page frames fra fil. Pages skal
// ligge sortert pÃ¥ ankomsttid. Alle data mÃ¥ vÃ¦re ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id load last R M
//    id load last R M
//    id load last R M
//    ...
//
void read_file(char *filename)
{
   int i;
   FILE *p_file;
   
   // Ã…pner fil og sjekker for feil i Ã¥pning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   { 
      printf("Feil ved Ã¥pning av filen \"%s\"\n", filename); 
      exit(-1);
   }

   // Leser antall page frames
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle pages
   PF = (struct page_frame *) malloc(N * sizeof(struct page_frame));

   // Leser inn en og en page frame.
   for (i = 0; i < N; i++)
      fscanf(p_file, "%d %d %d %d %d", &PF[i].id, &PF[i].load,
	      &PF[i].last, &PF[i].R, &PF[i].M);
   fclose(p_file);
}

//first_in_first_out(): Simulering av page replacement med FIFO
void first_in_first_out()
{
   // Skal programmeres ferdig i oppgave 1
   printf("\nFirst-In-First-Out:");

   if (N <= 0)
   {
      printf("Ingen page frames Ã¥ evaluere.\n");
      return;
   }

   // Vi antar at den fÃ¸rste pagen (indeks 0) er den eldste, 
   // men vi gjÃ¸r et sÃ¸k for Ã¥ vÃ¦re helt sikre pÃ¥ Ã¥ finne laveste 'load'.
   int fifo_index = 0;
   int min_load = PF[0].load;

   for (int i = 1; i < N; i++)
   {
      if (PF[i].load < min_load)
      {
         min_load = PF[i].load;
         fifo_index = i;
      }
   }

   printf("\npage	loaded	last ref	R	M");
   printf("\n%d	%d	%d		%d	%d\n", PF[fifo_index].id, PF[fifo_index].load, PF[fifo_index].last,
	PF[fifo_index].R, PF[fifo_index].M);
}

//least_recently_used(): Simulering av page replacement med LRU
void least_recently_used()
{
  // Skal programmeres ferdig i oppgave 2
  printf("\nleast recently used");

   if (N <= 0)
   {
      printf("Ingen page frames Ã¥ evaluere.\n");
      return;
   }

   // Vi antar at den fÃ¸rste pagen (indeks 0) er den eldste,
   // men vi gjÃ¸r et sÃ¸k for Ã¥ vÃ¦re helt sikre pÃ¥ Ã¥ finne laveste 'last'.
   int lru_index = 0;
   int min_last = PF[0].last;

   for (int i = 1; i < N; i++)
   {
      if (PF[i].last < min_last)
      {
         min_last = PF[i].last;
         lru_index = i;
      }
   }

   printf("\npage	loaded	last ref	R	M");
   printf("\n%d	%d	%d		%d	%d\n", PF[lru_index].id, PF[lru_index].load, PF[lru_index].last,
	PF[lru_index].R, PF[lru_index].M);
}

//second_chance(): Simulering av page replacement med Second Chance
void second_chance()
{
   // Skal programmeres ferdig i oppgave 3

   printf("\nSecond chance:");

   if (N <= 0)
   {
      printf("Ingen page frames Ã¥ evaluere.\n");
      return;
   }

   // Vi antar at den fÃ¸rste pagen (indeks 0) er den eldste,
   // men vi gjÃ¸r et sÃ¸k for Ã¥ vÃ¦re helt sikre pÃ¥ Ã¥ finne laveste 'load'.
   int sc_index = 0;
   int min_load = PF[0].load;

   for (int i = 1; i < N; i++)
   {
      if (PF[i].load < min_load)
      {
         min_load = PF[i].load;
         sc_index = i;
      }
   }

   // Sjekk R-biten og gi ny sjans om den er 1
   while (1)
   {
	if (PF[sc_index].R == 0)
      	{
         	break; // Pagen har R=0 og skal byttes ut
      	}
      	else
      	{
         	PF[sc_index].R = 0;
         	PF[sc_index].load = T; // Oppdaterer load-tid slik at den skyves bak i kÃ¸en

         	// Finn den neste eldste pagen
         	sc_index = 0;
         	min_load = PF[0].load;
         	for (int i = 1; i < N; i++)
         	{
            		if (PF[i].load < min_load)
            		{
               			min_load = PF[i].load;
               			sc_index = i;
            		}
         	}
      	}
   }
   	printf("\npage	loaded	last ref	R	M");
   	printf("\n%d	%d	%d		%d	%d\n", PF[sc_index].id, PF[sc_index].load, PF[sc_index].last,
	PF[sc_index].R, PF[sc_index].M);

}

// main(): Leser filnavn med page frame data, leser inndata fra fil og
// kjÃ¸rer tre ulike page replacement algoritmer
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer page replacement
   first_in_first_out();
   least_recently_used();
   second_chance();
}
