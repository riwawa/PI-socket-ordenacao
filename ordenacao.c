#include <stdio.h>

void trocar(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
int partition(int vetor[], int low, int high) {
	int pivo = vetor[low]; // escolhe o pivo
	int k = high;
	
	// iteracao vai de forma decrescente
	// se o elemento atual é maior que o pivo, 
	// trocar com o elemento no indice k e decrementa k
	//
	// ex: - pivo: 5
	//     - elemento atual: 6
	//     troca com o elemento no indice k (que ta no high/fim)
	for (int i = high; i > low; i--){
		if (vetor[i]>pivo) trocar(&vetor[i], &vetor[k--]);
	}
	// trocar o pivo com o elemento do indice k
	trocar(&vetor[low], &vetor[k]);

	return k;
}

void quicksort(int vetor[], int inicio, int fim){
	if(inicio<fim){
		int idx= partition(vetor, inicio, fim);

		quicksort(vetor, inicio, idx-1);
		quicksort(vetor, idx + 1, fim);
	}
}




