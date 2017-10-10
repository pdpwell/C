float direto(int cacheTam, int blockTam){
	FILE *traces;
	char line[50];
	int i;
	cache mcache[cacheTam/blockTam];
	int clin=cacheTam/blockTam;
	int cacheHit=0;
	int cacheMiss=0;
	int clinTam = log(clin)/log(2);
	int wordTam = log(blockTam)/log(2);
	int tagTam = (32-wordTam-clinTam);
	unsigned int tagBase=0;
	unsigned int clinBase=0;
	unsigned int end = 0;
	for(i=0;i<clinTam;i++){
		clinBase<<=1;
		clinBase|= 0x01;
	}

	for(i=0;i<tagTam;i++){
		tagBase<<=1;
		tagBase|= 0x01;
	}

	tagBase<<=clinTam+wordTam;
	clinBase<<=wordTam;

	for(i=0;i<clin;i++){
		mcache[i].val=0;
	}

	traces=fopen("trace","r");

	while(fscanf(traces,"%s",line)!= EOF ){

		end = (unsigned int)strtol(line, NULL, 16);
		int mcacheline= (end & clinBase) >> wordTam;
		if(mcache[mcacheline].val == 0){
			mcache[mcacheline].tag= end & tagBase;
			mcache[mcacheline].val=1;
			cacheMiss++;
		}
		else if(mcache[ mcacheline ].tag == (end & tagBase) ){
			cacheHit++;
		}
		else{
			mcache[mcacheline].tag = end & tagBase;
			cacheMiss++;
		}
	}
	int total=cacheHit+cacheMiss;
	float hitper=(cacheHit*100)/(float)total;
	return hitper;

}
