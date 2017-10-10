float associativoConjunto(int n,int cacheTam, int blockTam, int subPolit){
	int i,j;
	FILE *traces;
	char linhas[20];
	int quantidadeLinhas = (cacheTam/blockTam)/n;
	cache mcache[quantidadeLinhas][n];
	int tamanhoConjunto = log(quantidadeLinhas)/log(2);
	int tamanhoPalavra = log(blockTam)/log(2);
	int tamanhoTag = 32-tamanhoConjunto-tamanhoPalavra;
	unsigned int tagBase=0;
	unsigned int conjBase=0;
	unsigned int end = 0;
	int cacheHit=0;
	int cacheMiss=0;
	int auxval;
	int auxind=0;
	int time=0;

	for(i=0;i<tamanhoConjunto;i++){
		conjBase<<=1;
		conjBase|= 0x01;
	}

	for(i=0;i<tamanhoTag;i++){
		tagBase<<=1;
		tagBase|= 0x01;
	}

	for(i=0;i<quantidadeLinhas;i++){
		for (j=0;j<n;j++){
			mcache[i][j].val=0;
		}
	}

	tagBase<<=tamanhoConjunto+tamanhoPalavra;
	conjBase<<=tamanhoPalavra;

	traces=fopen("trace","r");

	while(fscanf(traces,"%s",linhas)!= EOF ){

		end = (unsigned int)strtol(linhas, NULL, 16);
		int mcacheline= (end & conjBase) >> tamanhoPalavra;


		for(i=0;i<n;i++){
			if(mcache[mcacheline][n-i-1].val == 0){
				mcache[mcacheline][n-i-1].tag = end & tagBase;
				mcache[mcacheline][n-i-1].time=time;
				mcache[mcacheline][n-i-1].val=1;
				cacheMiss++;
				break;
			}
			else{
				if(mcache[mcacheline][n-i-1].tag == (end & tagBase)){
					mcache[mcacheline][n-i-1].time=time;
					cacheHit++;
					break;
				}

			}
		}

		if(i==n){
			switch (subPolit){
				case 1://FIFO
					for(i=0;i<(n-1);i++){
						mcache[mcacheline][n-i-1]=mcache[mcacheline][n-i-2];
					}
					mcache[mcacheline][0].tag = end & tagBase;
					cacheMiss++;
					break;
				case 2://LRU
					auxval=mcache[mcacheline][0].time;
					for(i=1;i<n;i++){
						if(mcache[mcacheline][i].time < auxval){
							auxval=mcache[mcacheline][i].time;
							auxind=i;
						}
					}
					mcache[mcacheline][auxind].tag= end & tagBase;
					mcache[mcacheline][auxind].time=time;
					cacheMiss++;
					break;

			}
		}
		time++;
	}

	int total=cacheMiss+cacheHit;
	float hitper= (cacheHit*100)/(float)total;
	//printf ("Cache Hit: %d\n",cacheHit);
	return hitper;

}
