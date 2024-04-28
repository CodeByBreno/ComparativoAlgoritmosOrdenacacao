void insertionSort(int vet[], int low, int high) {
    int aux;
    
    for(int i=1 ; i<= high ; i++) {
        	int j=i;
        	while(j>0 && vet[j-1]>vet[j]) {
            	aux=vet[j];
            	vet[j]=vet[j-1];
            	vet[j-1]=aux;
           		j=j-1;
                timesInFor++;
        	}
      }
  }