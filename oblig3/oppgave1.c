#include <strcmp.h>
#include <stdio.h>
#include <stdlib.h>

int palindrom(char *s1){
	char bokstav;
	int lengde = strlen(*s1);
	char s2[] = (char *) malloc((lengde * sizeof(char))+1);
	s2=*s1;
	for (i=0; i<lengde/2; i++){
		bokstav = s2[i];
		s2 = s2[lengde-i-1];
		s2[lengde-i-1] = bokstav;
	}
	strcmp(*s1, s2);
	free(s2);
}

void main(){
	char s1[] = "abcde";
	palindrom(s1);
}
