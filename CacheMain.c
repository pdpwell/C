#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"
#include "associativo.c"
#include "direto.c"

int main (){
	int cacheTAM[5]={1024,2048,4096,8192,16384};
	int cacheways[3]={2,4,8};
	char str [] = ("Direto");
	char str0 [] = ("2 Way");
	char str1 [] = ("4 Way");
	char str2 [] = ("8 Way");

	int i;
	FILE *results;
	int op;

	//printf ("#\tDirect\t2-Way\t4-way\t8-Way\n");
	printf("FIFO	First In First Out\n");	
	for(int j=0; j<5; j++){
		
		printf ("%d Bytes\n",cacheTAM[j]);
		printf ("%s\t",str);
		printf ("%.3f%%\n",direto(cacheTAM[j],16));

		for(i=0;i<3;i++){
			switch (i+1) {
				case 1:
					printf ("%s\t",str0);
				break;

				case 2:
					printf ("%s\t",str1);
				break;

				case 3:
					printf ("%s\t",str2);
				break;
			}
			printf ("%.3f%%\n",associativoConjunto(cacheways[i],cacheTAM[j],16,1));
		}

		printf( "\n");
	}

	printf("\n");

	//printf ("#\tDirect\t2-Way\t4-way\t8-Way\n");
	printf("LRU		Least Recently Used\n");	
	for(int j=0; j<5; j++){
		printf ("%d\n",cacheTAM[j]);
		//printf("");
		printf ("Percentual de Acertos: %.3f%%\n",direto(cacheTAM[j],16));

		for(i=0;i<3;i++){

			printf ("Percentual de Acertos: %.3f%%\n",associativoConjunto(cacheways[i],cacheTAM[j],16,2));
		}

		printf( "\n");
	}

	return 0;
}
