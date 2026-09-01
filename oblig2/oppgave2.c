#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  	int i, r;
	int t[1000];

   	// Initierer trekkingen av tilfeldige tall med nÃ¥vÃ¦rende tid som "seed"
   	srand(time(NULL));
	int lengde = sizeof(t) / sizeof(t[0]); //antall elementer

   	for (i = 0; i < lengde; i++){
      		// Trekker et tilfeldig tall r, 0 <= r < 100 000
      		r = rand() % 100000;
		if (r < 100000){
      			t[i] = r;
			printf("%d\n", r);
		}
		else{
			continue;
		}
   	}

	int minst_tall = t[0];
	int storst_tall = t[1000];
	for (i = 0; i < lengde; i++){
		if (minst_tall > t[i]){
			minst_tall = t[i];
		}
		if (storst_tall < t[i]){
			storst_tall = t[i];
		}
	}
	printf("\nminste tall i tabellen: %d\n", minst_tall);
	printf("\nstorste tall i tabellen: %d\n", storst_tall);
}