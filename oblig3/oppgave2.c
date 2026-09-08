#include <stdio.h>
#include <stdlib.h>

int omvendt_rekkefoelge(int n) {

	int *A = (int *) malloc((n) * sizeof(int));
	if (A == NULL) {
		return 0; // FeilhÃ¥ndtering dersom minneallokeringen feiler
	}
	int *startpeker = A;
	printf("skriv selve tallene:\n");
	for (int i = 0; i < n; i++){
		scanf("%d", A);
		A++;
	}

	printf("\narray i omvendt rekkefoelge:\n");
	// Kopiere alle tegnene i omvendt rekkefÃ¸lge
	for (int i = 0; i < n; i++) {
		A--;
		printf("%d\n", *A);
	}

	free(startpeker);
}

int main() {
	int n;
	printf("skriv antall tall i array:\n");
	scanf("%d", &n);
	omvendt_rekkefoelge(n);
}